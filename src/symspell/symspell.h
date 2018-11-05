#pragma once

#define USE_GOOGLE_DENSE_HASH_MAP
//#define ENABLE_TEST
#define IO_OPERATIONS

#undef ENABLE_TEST

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <fstream>
#include <list>

#ifdef IO_OPERATIONS
#include <msgpack.hpp>
#endif

#ifdef USE_GOOGLE_DENSE_HASH_MAP
#include <sparsehash/dense_hash_map>
#include <sparsehash/dense_hash_set>

#define CUSTOM_SET google::dense_hash_set
#define CUSTOM_MAP google::dense_hash_map
#else
#include <map>
#include <set>

#define CUSTOM_SET std::set
#define CUSTOM_MAP std::map
#endif


#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((a) > (b)) ? (a) : (b))

#define getHastCode(term) std::hash<std::string>()(term)


class dictionaryItem {
public:
	std::vector<size_t> suggestions;
	size_t count = 0;

	dictionaryItem(size_t c)
	{
		count = c;
	}

	dictionaryItem()
	{
		count = 0;
	}
	~dictionaryItem()
	{
		suggestions.clear();
	}

#ifdef IO_OPERATIONS
	MSGPACK_DEFINE(suggestions, count);
#endif
};

enum ItemType { NONE, DICT, INTEGER };

#ifdef IO_OPERATIONS
MSGPACK_ADD_ENUM(ItemType);
#endif

class dictionaryItemContainer
{
public:
	dictionaryItemContainer() : itemType(NONE), intValue(0)
	{
	}

	ItemType itemType;
	size_t intValue;
	std::shared_ptr<dictionaryItem> dictValue;

#ifdef IO_OPERATIONS
	MSGPACK_DEFINE(itemType, intValue, dictValue);
#endif
};

class suggestItem
{
public:
	std::string term;
	unsigned short distance = 0;
	unsigned short count;

	bool operator== (const suggestItem & item) const
	{
		return term.compare(item.term) == 0;
	}

	size_t HastCode() const
	{
		return std::hash<std::string>()(term);
	}

#ifdef IO_OPERATIONS
	MSGPACK_DEFINE(term, distance, count);
#endif
};

class SymSpell {
public:
	size_t verbose = 1;
	size_t editDistanceMax = 2;

	SymSpell()
	{
#ifdef USE_GOOGLE_DENSE_HASH_MAP
		dictionary.set_empty_key(0);
#endif
	}

	void CreateDictionary(std::string corpus)
	{
		std::ifstream sr(corpus);

		if (!sr.good())
		{
			std::cout << "File not found: " << corpus;
			return;
		}

		std::cout << "Creating dictionary ..." << std::endl;

		long wordCount = 0;

		for (std::string line; std::getline(sr, line); ) {

			for (const std::string & key : parseWords(line))
			{
				if (CreateDictionaryEntry(key)) ++wordCount;
			}
		}

		sr.close();
	}

#ifdef IO_OPERATIONS

	void Save(std::string filePath)
	{
		std::ofstream fileStream(filePath, std::ios::binary);

		if (fileStream.good())
		{
#ifdef USE_GOOGLE_DENSE_HASH_MAP
			std::unordered_map<size_t, dictionaryItemContainer> tmpDict(dictionary.begin(), dictionary.end()); // should be undered_map
#endif

			msgpack::packer<std::ofstream> packer(&fileStream);

			packer.pack(this->verbose);
			packer.pack(this->editDistanceMax);
			packer.pack(this->maxlength);

#ifdef USE_GOOGLE_DENSE_HASH_MAP
			packer.pack(tmpDict);
#else
			packer.pack(dictionary);
#endif
			packer.pack(this->wordlist);
		}

		fileStream.close();
	}
	
	void Load(std::string fileContent)
	{
        msgpack::unpacker packer;

        packer.reserve_buffer(fileContent.length());
        memcpy(packer.buffer(), fileContent.data(), fileContent.length());
        packer.buffer_consumed(fileContent.length());

        msgpack::object_handle handler;
        packer.next(handler);

        handler.get().convert(this->verbose);
        packer.next(handler);

        handler.get().convert(this->editDistanceMax);
        packer.next(handler);

        handler.get().convert(this->maxlength);
        packer.next(handler);

#ifdef USE_GOOGLE_DENSE_HASH_MAP
        std::unordered_map<size_t, dictionaryItemContainer> tmpDict;
        handler.get().convert(tmpDict);
        this->dictionary.insert(tmpDict.begin(), tmpDict.end());
#else
        handler.get().convert(this->dictionary);
#endif
        packer.next(handler);
        handler.get().convert(this->wordlist);
	}

#endif

	bool CreateDictionaryEntry(std::string key)
	{
		bool result = false;
		dictionaryItemContainer value;

		auto dictionaryEnd = dictionary.end(); // for performance
		auto valueo = dictionary.find(getHastCode(key));
		if (valueo != dictionaryEnd)
		{
			value = valueo->second;

			if (valueo->second.itemType == ItemType::INTEGER)
			{
				value.itemType = ItemType::DICT;
				value.dictValue = std::make_shared<dictionaryItem>();
				value.dictValue->suggestions.push_back(valueo->second.intValue);
			}
			else
				value = valueo->second;

			if (value.dictValue->count < INT_MAX)
				++(value.dictValue->count);
		}
		else if (wordlist.size() < INT_MAX)
		{
			value.itemType = ItemType::DICT;
			value.dictValue = std::make_shared<dictionaryItem>();
			++(value.dictValue->count);
			std::string mapKey = key;
			dictionary.insert(std::pair<size_t, dictionaryItemContainer>(getHastCode(mapKey), value));
			dictionaryEnd = dictionary.end(); // for performance

			if (key.size() > maxlength)
				maxlength = key.size();
		}

		if (value.dictValue->count == 1)
		{
			wordlist.push_back(key);
			size_t keyint = wordlist.size() - 1;

			result = true;

			auto deleted = CUSTOM_SET<std::string>();
#ifdef USE_GOOGLE_DENSE_HASH_MAP
			deleted.set_empty_key("");
#endif

			Edits(key, deleted);

			for (std::string del : deleted)
			{
				auto value2 = dictionary.find(getHastCode(del));
				if (value2 != dictionaryEnd)
				{
					if (value2->second.itemType == ItemType::INTEGER)
					{
						value2->second.itemType = ItemType::DICT;
						value2->second.dictValue = std::make_shared<dictionaryItem>();
						value2->second.dictValue->suggestions.push_back(value2->second.intValue);
						dictionary[getHastCode(del)].dictValue = value2->second.dictValue;

						if (std::find(value2->second.dictValue->suggestions.begin(), value2->second.dictValue->suggestions.end(), keyint) == value2->second.dictValue->suggestions.end())
							AddLowestDistance(value2->second.dictValue, key, keyint, del);
					}
					else if (std::find(value2->second.dictValue->suggestions.begin(), value2->second.dictValue->suggestions.end(), keyint) == value2->second.dictValue->suggestions.end())
						AddLowestDistance(value2->second.dictValue, key, keyint, del);
				}
				else
				{
					dictionaryItemContainer tmp;
					tmp.itemType = ItemType::INTEGER;
					tmp.intValue = keyint;

					dictionary.insert(std::pair<size_t, dictionaryItemContainer>(getHastCode(del), tmp));
					dictionaryEnd = dictionary.end();
				}
			}
		}
		return result;
	}

	std::vector<suggestItem> Correct(std::string input)
	{
		std::vector<suggestItem> suggestions;

#ifdef ENABLE_TEST
		using namespace std::chrono;

		high_resolution_clock::time_point t1 = high_resolution_clock::now();

		for (size_t i = 0; i < 100000; ++i)
		{
			Lookup(input, editDistanceMax);
		}

		high_resolution_clock::time_point t2 = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

		std::cout << "It took me " << time_span.count() << " seconds.";
		std::cout << std::endl;
#endif
		suggestions = Lookup(input, editDistanceMax);
		return suggestions;

	}

private:
	size_t maxlength = 0;
	CUSTOM_MAP<size_t, dictionaryItemContainer> dictionary;
	std::vector<std::string> wordlist;

	std::vector<std::string> parseWords(std::string text) const
	{
		std::vector<std::string> returnData;

		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		std::regex word_regex("[^\\W\\d_]+");
		auto words_begin = std::sregex_iterator(text.begin(), text.end(), word_regex);
		auto words_end = std::sregex_iterator();

		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			returnData.push_back(match.str());
		}

		return returnData;
	}

	void AddLowestDistance(std::shared_ptr<dictionaryItem> const & item, std::string suggestion, size_t suggestionint, std::string del)
	{
		if ((verbose < 2) && (item->suggestions.size() > 0) && (wordlist[item->suggestions[0]].size() - del.size() > suggestion.size() - del.size()))
			item->suggestions.clear();

		if ((verbose == 2) || (item->suggestions.size() == 0) || (wordlist[item->suggestions[0]].size() - del.size() >= suggestion.size() - del.size()))
			item->suggestions.push_back(suggestionint);
	}

	void Edits(std::string word, CUSTOM_SET<std::string> & deletes) const
	{
		CUSTOM_MAP<size_t, const char *> queue;
#ifdef USE_GOOGLE_DENSE_HASH_MAP
		queue.set_empty_key(0);
#endif
		queue.insert(std::pair<size_t, const char*>(getHastCode(word), word.c_str()));

		for (size_t d = 0; d < editDistanceMax; ++d)
		{
			CUSTOM_MAP<size_t, const char *> tempQueue;
			auto tempQueueEnd = tempQueue.end();
#ifdef USE_GOOGLE_DENSE_HASH_MAP
			tempQueue.set_empty_key(0);
#endif

			for (auto item : queue) {
				if (strlen(item.second)) {
					for (size_t i = 0; i < strlen(item.second); ++i)
					{
						// For Performance ->
						char* del = static_cast<char *>(malloc(strlen(item.second) + 1));

						strcpy(del, item.second);
						size_t k = i;
						int len = strlen(item.second);
						for (; k < len - 1; k++)
							del[k] = item.second[k + 1];
						del[k] = '\0';
						// <- For Performance
						
						if (*del == '\0') // eigen inbreng
						{
							free(del);
							continue;
						}
						
						if (!deletes.count(del))
							deletes.insert(del);

						if (tempQueue.find(getHastCode(del)) == tempQueueEnd)
						{
							tempQueue.insert(std::pair<size_t, const char*>(getHastCode(del), del));
							tempQueueEnd = tempQueue.end();
						}
					}
				}
			}
			queue = tempQueue;
		}
	}

	std::vector<suggestItem> Lookup(std::string input, size_t editDistanceMax)
	{
		if (input.size() - editDistanceMax > maxlength)
			return std::vector<suggestItem>();

		std::vector<std::string> candidates;
		candidates.reserve(2048);
		CUSTOM_SET<size_t> hashset1;
#ifdef USE_GOOGLE_DENSE_HASH_MAP
		hashset1.set_empty_key(0);
#endif

		std::vector<suggestItem> suggestions;
		CUSTOM_SET<size_t> hashset2;
#ifdef USE_GOOGLE_DENSE_HASH_MAP
		hashset2.set_empty_key(0);
#endif

		//object valueo;

		candidates.push_back(input);
		auto dictionaryEnd = dictionary.end();

		size_t candidatesIndexer = 0; // for performance
		while ((candidates.size() - candidatesIndexer) > 0)
		{
			std::string candidate = candidates[candidatesIndexer];
			size_t candidateSize = candidate.size(); // for performance
			++candidatesIndexer;

			if ((verbose < 2) && (suggestions.size() > 0) && (input.size() - candidateSize > suggestions[0].distance))
				goto sort;

			auto valueo = dictionary.find(getHastCode(candidate));

			//read candidate entry from dictionary
			if (valueo != dictionaryEnd)
			{
				if (valueo->second.itemType == ItemType::INTEGER)
				{
					valueo->second.itemType = ItemType::DICT;
					valueo->second.dictValue = std::make_shared<dictionaryItem>();
					valueo->second.dictValue->suggestions.push_back(valueo->second.intValue);
				}


				if (valueo->second.itemType == ItemType::DICT &&
					valueo->second.dictValue->count > 0 &&
					hashset2.insert(getHastCode(candidate)).second)
				{
					//add correct dictionary term term to suggestion list
					suggestItem si;
					si.term = candidate;
					si.count = valueo->second.dictValue->count;
					si.distance = input.size() - candidateSize;
					suggestions.push_back(si);
					//early termination
					if ((verbose < 2) && (input.size() - candidateSize == 0))
						goto sort;
				}

				for (size_t suggestionint : valueo->second.dictValue->suggestions)
				{
					//save some time
					//skipping double items early: different deletes of the input term can lead to the same suggestion
					//index2word
					std::string suggestion = wordlist[suggestionint];
					if (hashset2.insert(getHastCode(suggestion)).second)
					{
						size_t distance = 0;
						if (suggestion != input)
						{
							if (suggestion.size() == candidateSize) distance = input.size() - candidateSize;
							else if (input.size() == candidateSize) distance = suggestion.size() - candidateSize;
							else
							{
								size_t ii = 0;
								size_t jj = 0;
								while ((ii < suggestion.size()) && (ii < input.size()) && (suggestion[ii] == input[ii]))
									++ii;

								while ((jj < suggestion.size() - ii) && (jj < input.size() - ii) && (suggestion[suggestion.size() - jj - 1] == input[input.size() - jj - 1]))
									++jj;
								if ((ii > 0) || (jj > 0))
									distance = DamerauLevenshteinDistance(suggestion.substr(ii, suggestion.size() - ii - jj), input.substr(ii, input.size() - ii - jj));
								else
									distance = DamerauLevenshteinDistance(suggestion, input);

							}
						}

						if ((verbose < 2) && (suggestions.size() > 0) && (suggestions[0].distance > distance))
							suggestions.clear();

						if ((verbose < 2) && (suggestions.size() > 0) && (distance > suggestions[0].distance))
							continue;

						if (distance <= editDistanceMax)
						{
							auto value2 = dictionary.find(getHastCode(suggestion));

							if (value2 != dictionaryEnd)
							{
								suggestItem si;
								si.term = suggestion;
								if (value2->second.itemType == ItemType::DICT)
									si.count = value2->second.dictValue->count;
								else
									si.count = 1;
								si.distance = distance;
								suggestions.push_back(si);
							}
						}
					}
				}
			}


			if (input.size() - candidateSize < editDistanceMax)
			{
				if ((verbose < 2) && (suggestions.size() > 0) && (input.size() - candidateSize >= suggestions[0].distance))
					continue;

				for (size_t i = 0; i < candidateSize; ++i)
				{
					std::string wordClone = candidate;
					std::string & del = wordClone.erase(i, 1);
					if (hashset1.insert(getHastCode(del)).second)
						candidates.push_back(del);
				}
			}
		}//end while

		 //sort by ascending edit distance, then by descending word frequency
	sort:
		if (verbose < 2)
			sort(suggestions.begin(), suggestions.end(), Xgreater1());
		else
			sort(suggestions.begin(), suggestions.end(), Xgreater2());

		if ((verbose == 0) && (suggestions.size() > 1))
			return std::vector<suggestItem>(suggestions.begin(), suggestions.begin() + 1);
		else
			return suggestions;
	}

	struct Xgreater1
	{
		bool operator()(const suggestItem& lx, const suggestItem& rx) const {
			return lx.count > rx.count;
		}
	};

	struct Xgreater2
	{
		bool operator()(const suggestItem& lx, const suggestItem& rx) const {
			auto cmpForLx = 2 * (lx.distance - rx.distance) - (lx.count - rx.count);
			auto cmpForRx = 2 * (rx.distance - lx.distance) - (rx.count - lx.count);
			return cmpForLx > cmpForRx;
		}
	};


	static size_t DamerauLevenshteinDistance(const std::string &s1, const std::string &s2)
	{
		const size_t m(s1.size());
		const size_t n(s2.size());

		if (m == 0) return n;
		if (n == 0) return m;

		size_t *costs = new size_t[n + 1];

		for (size_t k = 0; k <= n; ++k) costs[k] = k;

		size_t i = 0;
		auto s1End = s1.end();
		auto s2End = s2.end();
		for (std::string::const_iterator it1 = s1.begin(); it1 != s1End; ++it1, ++i)
		{
			costs[0] = i + 1;
			size_t corner = i;

			size_t j = 0;
			for (std::string::const_iterator it2 = s2.begin(); it2 != s2End; ++it2, ++j)
			{
				size_t upper = costs[j + 1];
				if (*it1 == *it2)
				{
					costs[j + 1] = corner;
				}
				else
				{
					size_t t(upper < corner ? upper : corner);
					costs[j + 1] = (costs[j] < t ? costs[j] : t) + 1;
				}

				corner = upper;
			}
		}

		size_t result = costs[n];
		delete[] costs;

		return result;
	}
};

#undef max
#undef min