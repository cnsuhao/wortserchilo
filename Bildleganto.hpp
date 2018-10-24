#ifndef WORTSERCXILO_EKRANLEGANTO_HPP
#define WORTSERCXILO_EKRANLEGANTO_HPP

#include <QtCore/QThread>
#include <QtCore/QCoreApplication>
#include "LegitaWorto.hpp"
#include "komuna/PropraAdres.hpp"
#include "komuna/traduko/Linguo.hpp"
#include "komuna/komunikad/Promeso.hpp"

class RealigoDeBildleganto;

class Bildleganto : public QObject
{
    friend class RealigoDeBildleganto;
Q_OBJECT
public:
    explicit Bildleganto(PropraAdres<RealigoDeBildleganto>&& p_realigo);
    ~Bildleganto() override;
    Texto nomon() const;
    
    Promesita<Listo<Texto>> donuElekteblajnLinguojn();
    
    // licas ke oni alvokas ĉi-tion dum legi bildon
    Nenio kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero);
signals:
    Nenio kiamProgresas(float progreso);
    Nenio kiamHavasRezulton(RezultoDeLegado rezulto);
public slots:
    Nenio leguDosieron(Texto bilddosiero) { QMetaObject::invokeMethod(this, "_komencu", Q_ARG(Texto, bilddosiero)); };
    Nenio nuligu() { QMetaObject::invokeMethod(this, "_nuligu"); }
    Nenio reagorduLinguojn(const Listo<Texto>& linguoj) { QMetaObject::invokeMethod(this, "_reagorduLinguojn", Q_ARG(Listo<Texto>, linguoj)); }
private slots:
    Nenio _komencu(Texto bilddosiero);
    Nenio _nuligu() { ĉuNuligis = veran; }
    Nenio _reagorduLinguojn(Listo<Texto> linguoj);
    Nenio _donuElekteblajnLinguojn(DividataAdres<Promeso<Listo<Texto>>> promeso);
private:
    Nenio traktuDosieron(Texto bilddosiero);
    PropraAdres<RealigoDeBildleganto> realigo;
    Texto prokrastitaBilddosiero;
    Listo<Texto> prokrastitaListoDeNovajLinguoj;
    Buleo ĉuJamLegasBildon; // Por simpleco ni nur traktas unu bildon samtempe.
    Buleo ĉuNuligis;
    QThread fadeno;
};

class RealigoDeBildleganto
{
    friend class Bildleganto;
public:
    struct Rezulto { RezultoDeLegado rezulto; Buleo ĉuEstasValidanRezulton; };
    RealigoDeBildleganto() : bildleganto(nullptr) {}
    virtual ~RealigoDeBildleganto() = default;
    virtual Texto nomon() const = 0;
    virtual Rezulto leguBildon(const Texto& bilddosiero) = 0;
    virtual Listo<Texto> donuElekteblajnLinguojn() const = 0;
    virtual Nenio reagorduLinguojn(const Listo<Texto>& linguoj) = 0;
    virtual Nenio kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero) const;
protected:
    Nenio raportuProgreson(ℚ4 progreso) { bildleganto->kiamProgresas(progreso); } //-«
    Buleo ĉuNuligis() const { QCoreApplication::processEvents(); eligu bildleganto->ĉuNuligis; }
private:
    Nenio agorduBildleganton(Bildleganto* p) { premisu(bildleganto == nullptr); bildleganto = p; } //»-
    Bildleganto* bildleganto;
};

Nenio kreuBlanknigranVersionDe(const Texto& koloraBildo, const Texto& celdosiero);

#endif //WORTSERCXILO_EKRANLEGANTO_HPP
