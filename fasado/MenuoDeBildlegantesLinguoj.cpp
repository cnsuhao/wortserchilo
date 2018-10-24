#include "MenuoDeBildlegantesLinguoj.hpp"

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QHeaderView>
#include "MenuoDeBildlegantesLinguoj.hpp"
#include "../komuna/alTexto.hpp"

MenuoDeBildlegantesLinguoj::MenuoDeBildlegantesLinguoj(QWidget* patro) : QWidget(patro), fLinguojDeBildleganto(nullptr),
        /*todo*/ linguoDeFasado(esperanta_linguo)
{
    aranĝanto = kreu AranĝantoKunAnimacioj(this);
    kapo = kreu QLabel(aranĝanto);
    fElektitajLinguojDeBildleganto = kreu QTreeWidget(aranĝanto);
    fLinguojDeBildleganto = kreu QTreeWidget(aranĝanto);
    
    kapo->setObjectName("kapo");
    fElektitajLinguojDeBildleganto->setSelectionBehavior(QAbstractItemView::SelectRows);
    fElektitajLinguojDeBildleganto->setSelectionMode(QAbstractItemView::SingleSelection);
    fElektitajLinguojDeBildleganto->setTextElideMode(Qt::ElideNone);
    fElektitajLinguojDeBildleganto->header()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    
    fLinguojDeBildleganto->setSelectionBehavior(QAbstractItemView::SelectRows);
    fLinguojDeBildleganto->setSelectionMode(QAbstractItemView::SingleSelection);
    fLinguojDeBildleganto->setTextElideMode(Qt::ElideNone);
    fLinguojDeBildleganto->header()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    
    QVBoxLayout* krado = kreu QVBoxLayout(this);
    krado->setMargin(0);
    krado->setSpacing(0);
    krado->addWidget(aranĝanto, 1);
    
    kreuListonDeLinguojDeBildleganto();
    kreuListonDeElektitajLinguojDeBildleganto();
    preparuTextojn();
    rekreuAranĝon();
    
    connect(fElektitajLinguojDeBildleganto, &QTreeWidget::itemActivated, [this](QTreeWidgetItem* vico)
    {
        agorduĈuLinguoDeBildlegantoEstasElektitan(vico->text(0), malveran);
    });
    
    connect(fElektitajLinguojDeBildleganto, &QTreeWidget::itemSelectionChanged, [this]()
    {
        if (ne fElektitajLinguojDeBildleganto->selectedItems().empty())
            fLinguojDeBildleganto->clearSelection();
    });
    
    connect(fLinguojDeBildleganto, &QTreeWidget::itemActivated, [this](QTreeWidgetItem* vico)
    {
        agorduĈuLinguoDeBildlegantoEstasElektitan(vico->text(0), veran);
    });
    
    connect(fLinguojDeBildleganto, &QTreeWidget::itemSelectionChanged, [this]()
    {
        if (ne fLinguojDeBildleganto->selectedItems().empty())
            fElektitajLinguojDeBildleganto->clearSelection();
    });
}

Nenio MenuoDeBildlegantesLinguoj::agorduElekteblajnLinguojnPorBildleganto(Listo<Texto> p_linguoj)
{
    linguojDeBildleganto = formovu(p_linguoj);
    kreuListonDeLinguojDeBildleganto();
    Buleo ĉuŜanĝisElektitajnLinguojn = malveran;
    
    for (ℕ i = 0; i < elektitajLinguojDeBildleganto.grandon();)
    {
        if (ne linguojDeBildleganto.ĉuEnhavas(elektitajLinguojDeBildleganto[i]))
        {
            ĉuŜanĝisElektitajnLinguojn = veran;
            elektitajLinguojDeBildleganto.forprenu(i);
        }
        else i++;
    }
    
    for (const Texto& elektitaLinguo : elektitajLinguojDeBildleganto)
        markuLinguonDeBildleganto(elektitaLinguo, veran);
    
    if (ĉuŜanĝisElektitajnLinguojn)
        kiamOniElektisNovajnLinguojnPorBildleganto();
}

Nenio MenuoDeBildlegantesLinguoj::agorduĈuLinguoDeBildlegantoEstasElektitan(const Texto& nomo, Buleo ĉuEstasElektitan)
{
    if (ĉuEstasElektitan == elektitajLinguojDeBildleganto.ĉuEnhavas(nomo))
        eligu;
    
    if (ĉuEstasElektitan)
        elektitajLinguojDeBildleganto.enmetu(nomo);
    else elektitajLinguojDeBildleganto.forprenuĈiun(nomo);
    
    markuLinguonDeBildleganto(nomo, ĉuEstasElektitan);
    kreuListonDeElektitajLinguojDeBildleganto();
    kiamOniElektisNovajnLinguojnPorBildleganto();
    rekreuAranĝon();
}

Nenio MenuoDeBildlegantesLinguoj::agorduLinguonDeFasado(Linguo linguo)
{
    linguoDeFasado = linguo;
    kreuListonDeElektitajLinguojDeBildleganto();
    kreuListonDeLinguojDeBildleganto();
    rekreuAranĝon();
}

Nenio MenuoDeBildlegantesLinguoj::preparuTextojn()
{
    kapo->setText(tr("Linguoj de bildleganto"));
}

Nenio MenuoDeBildlegantesLinguoj::rekreuAranĝon()
{
    AranĝantoKunAnimacioj::Aranĝo aranĝo;
    ℤ altoDeElektitajLinguojDeBildleganto = 0;
    if (ne elektitajLinguojDeBildleganto.ĉuEstasMalplenan())
    {
        ℕ altoDeVico = fElektitajLinguojDeBildleganto->sizeHintForRow(0);
        altoDeElektitajLinguojDeBildleganto = elektitajLinguojDeBildleganto.grandon() * altoDeVico + 4;
        if (height() > 100)
            altoDeElektitajLinguojDeBildleganto = std::min(height() / 3, altoDeElektitajLinguojDeBildleganto);
    }
    
    aranĝo.anoj.enmetuNovan(kapo, 0, 0, 1, 0, 0, 0, 0, kapo->sizeHint().height());
    ℤ y = kapo->sizeHint().height();
    aranĝo.anoj.enmetuNovan(fElektitajLinguojDeBildleganto, 0, 0, 1, 0, 0, y, 0, altoDeElektitajLinguojDeBildleganto);
    y += altoDeElektitajLinguojDeBildleganto;
    aranĝo.anoj.enmetuNovan(fLinguojDeBildleganto, 0, 0, 1, 1, 0, y, 0, -y);
    
    aranĝanto->agorduAranĝonRulante(aranĝo);
}

Nenio MenuoDeBildlegantesLinguoj::kreuListonDeLinguojDeBildleganto()
{
    fLinguojDeBildleganto->clear();
    fLinguojDeBildleganto->setSortingEnabled(malveran);
    
    fLinguojDeBildleganto->setColumnCount(2);
    fLinguojDeBildleganto->setHeaderHidden(veran);
    
    for (const Texto& nomo : linguojDeBildleganto)
    {
        Linguo linguo(nomo);
        Texto nomoDeLinguo = linguo.donuNomon(linguoDeFasado);
        Texto montrataNomo = nomo;
        if (nomoDeLinguo != nomo)
            montrataNomo += "\t " + nomoDeLinguo;
        kreu QTreeWidgetItem(fLinguojDeBildleganto, {nomo.QT(), montrataNomo.QT()});
    }
    
    fLinguojDeBildleganto->hideColumn(0);
    fLinguojDeBildleganto->sortByColumn(1, Qt::AscendingOrder);
    fLinguojDeBildleganto->setSortingEnabled(veran);
}

Nenio MenuoDeBildlegantesLinguoj::kreuListonDeElektitajLinguojDeBildleganto()
{
    fElektitajLinguojDeBildleganto->clear();
    fElektitajLinguojDeBildleganto->setSortingEnabled(malveran);
    
    fElektitajLinguojDeBildleganto->setColumnCount(1);
    fElektitajLinguojDeBildleganto->setHeaderHidden(veran);
    
    for (const Texto& linguo : elektitajLinguojDeBildleganto)
        kreu QTreeWidgetItem(fElektitajLinguojDeBildleganto, {linguo.QT()});
    
    fElektitajLinguojDeBildleganto->sortByColumn(0, Qt::AscendingOrder);
    fElektitajLinguojDeBildleganto->setSortingEnabled(veran);
}

Nenio MenuoDeBildlegantesLinguoj::markuLinguonDeBildleganto(const Texto& nomo, Buleo ĉuEstasMarkitan)
{
    QList<QTreeWidgetItem*> rezulto = fLinguojDeBildleganto->findItems(nomo.QT(), Qt::MatchExactly, 0);
    
    for (QTreeWidgetItem* ano : rezulto)
        markuAnon(ano, ĉuEstasMarkitan);
}

Nenio MenuoDeBildlegantesLinguoj::markuAnon(QTreeWidgetItem* ano, Buleo ĉuEstasMarkitan) const
{
    for (ℕ i = 0; i < ano->columnCount(); i++)
    {
        ano->setForeground(i, ĉuEstasMarkitan ? elektita_textkoloro : fLinguojDeBildleganto->palette().foreground());
        ano->setBackground(i, ĉuEstasMarkitan ? elektita_fonkoloro : fLinguojDeBildleganto->palette().background());
    }
}