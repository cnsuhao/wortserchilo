## Instali Parsoid kun Mediawiki sur Debian
 - Prenu ŝutaĵon de la volata wikiwortaro el <https://dumps.wikimedia.org>.
 - Ŝarĝu paketojn. Mi verŝajne forgesis iujn paketojn sed erarmesaĝoj nepre diros kiujn vi mankas.
     ```
     sudo apt install mediawiki maven npm
     ```
 - Metu Mediawiki en vies reta dosierujo:
     ```
     sudo ln -s /usr/share/mediawiki /var/www/html/w
     ```
 - Instalu la Scribunto aldonon:
 
     Ŝarĝu el <https://www.mediawiki.org/wiki/Special:ExtensionDistributor/Scribunto> kaj elpaku ĝin ie-ajn.
     ```
     chmod a+x ./Scribunto/engines/LuaStandalone/binaries/lua5_1_5_linux_64_generic/lua
     sudo ln -s ./Scribunto /usr/share/mediawiki/extensions/Scribunto
     ```
 - Kreu datumbankon.
     ```
     mysql -u root -p
     ```
   Se vi ne memoras vies pasworton vi ankaŭ povas uzi `sudo mysql`.
   
   Tiam en MySQL:
     ```
     create database wikiwortaro;
     grant all privileges on wikiwortaro.* to 'wikiuzanto'@'localhost' identified by 'pasworto';
     quit;
     ```
   Nature licas ke vi elpensas proprajn nomojn por «wikiwortaro», «wikiuzanto» kaj «pasworto».
 - En retumilo iru al <http://localhost/w/> kaj uzu la instalilon por krei LocalSettings.php, uzu la datumbankon kaj
   uzanton kiujn vi ĵus kreis. 
   
   Elektu binaran tekston por la datumbanko.
    
   El la aldonoj ni nur bezonas ParserFunctions.
   
 - Metu la jenan al la fino de LocalSettings.php:
     ```
     ## Se vi ne instalis ĝin per instalilo.
     # wfLoadExtension('ParserFunctions');
     
     wfLoadExtension('Scribunto');
     $wgScribuntoDefaultEngine = 'luastandalone';
     
     ## Faras ke paĝnomoj distingas majusklojn kaj minusklojn,
     ## kion Wikiwortaroj bezonas sed normaj Mediawikioj ne volas.
     $wgCapitalLinks = false;
     ```
 - Metu LocalSettings.php en `/etc/mediawiki`. Poste <http://localhost/w/> devus montri funkciantan Mediawiki sen enhavon.
 - Instalu mwdumper, kiu legos la ŝutaĵon.
     ```
     git clone https://gerrit.wikimedia.org/r/p/mediawiki/tools/mwdumper
     cd mwdumper
     mvn compile
     mvn package
     ```
 - Legu sjablonojn kaj Lua-modulojn el la ŝutaĵo.
     ```
     java -jar ./target/mwdumper-1.25.jar --format=sql:1.25 --progress=100000 --filter=namespace:10,828 ŜUTAĴO | mysql -u wikiuzanto --database=wikiwortaro -p
     ```
   `«--filter=namespace:10,828»` signifas ke ni nur volas la sjablonojn (10) kaj Lua-modulojn (828). Sen tiuj argumentoj
   vi legus la tutan wortaron, kio daŭrus dum la plejparto de la tago.
   
   Se ĝi iam malfunkcias te antaŭ refari la komandon vi devos peti en mysql:
     ```
     connect wikiwortaro; 
     truncate table page; 
     truncate table text; 
     truncate table revision; 
     truncate table redirect;
     ```
   Se mwdumper ĝuste finis, <http://localhost/w/?title=Special%3APrefixIndex&namespace=10> devus montri grandan liston de
   sjablonoj.
 - Instalu Parsoid:
     ```
     git clone https://gerrit.wikimedia.org/r/p/mediawiki/services/parsoid
     cd parsoid
     npm install
     cp ./config.example.yaml ./config.yaml
     ```
   Se vi ne metis la wikiwortaron ĉe <http://localhost/w/> te vi devas ŝanĝi `config.yaml`.
 - Finfine rulu Parsoid:
     ```
     npm start
     ```
   Rulu la Iom Rapidan Wortaron kaj uzu `http://localhost:8000/localhost/v3/transform/wikitext/to/html/` kiel la retadreso de Parsoid.