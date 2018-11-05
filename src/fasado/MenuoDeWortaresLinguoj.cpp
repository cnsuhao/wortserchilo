#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QHeaderView>
#include "MenuoDeWortaresLinguoj.hpp"
#include "../komuna/alTexto.hpp"

MenuoDeWortaresLinguoj::MenuoDeWortaresLinguoj(QWidget* patro) : QWidget(patro), fWortaroj(nullptr),
        /*todo*/ linguoDeFasado(esperanta_linguo), ĉuMontrasFonton(malveran)
{
    aranĝanto = kreu AranĝantoKunAnimacioj(this);
    kapo = kreu QLabel(aranĝanto);
    informujo = kreu QTextEdit(aranĝanto);
    fElektitajWortaroj = kreu QTreeWidget(aranĝanto);
    fWortaroj = kreu QTreeWidget(aranĝanto);
    
    kapo->setObjectName("kapo");
    informujo->setReadOnly(veran);
    informujo->setObjectName("priskribo");
    
    fElektitajWortaroj->setSelectionBehavior(QAbstractItemView::SelectRows);
    fElektitajWortaroj->setSelectionMode(QAbstractItemView::SingleSelection);
    fElektitajWortaroj->setTextElideMode(Qt::ElideNone);
    fElektitajWortaroj->header()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    
    fWortaroj->setSelectionBehavior(QAbstractItemView::SelectRows);
    fWortaroj->setSelectionMode(QAbstractItemView::SingleSelection);
    fWortaroj->setTextElideMode(Qt::ElideNone);
    fWortaroj->header()->setSectionResizeMode(QHeaderView::ResizeMode::Interactive);
    
    
    QVBoxLayout* krado = kreu QVBoxLayout(this);
    krado->setMargin(0);
    krado->setSpacing(0);
    krado->addWidget(aranĝanto, 1);
    
    kreuListonDeWortaroj();
    kreuListonDeElektitajWortaroj();
    preparuTextojn();
    rekreuAranĝon();
    
    connect(fElektitajWortaroj, &QTreeWidget::itemActivated, [this](QTreeWidgetItem* vico)
    {
        agorduĈuWortaroEstasElektitan(vico->text(1), Linguo(vico->text(2)), malveran);
    });
    
    connect(fElektitajWortaroj, &QTreeWidget::itemSelectionChanged, [this]()
    {
        QList<QTreeWidgetItem*> elektoj = fElektitajWortaroj->selectedItems();
        if (elektoj.empty())
            eligu;
        fWortaroj->clearSelection();
        montruPriskribonDeWortaro(elektoj[0]->text(1), Linguo(elektoj[0]->text(2)));
    });
    
    connect(fWortaroj, &QTreeWidget::itemSelectionChanged, [this]()
    {
        QList<QTreeWidgetItem*> elektoj = fWortaroj->selectedItems();
        if (elektoj.empty())
            eligu;
        fElektitajWortaroj->clearSelection();
        montruPriskribonDeWortaro(elektoj[0]->text(1), Linguo(elektoj[0]->text(0)));
    });
    
    connect(fWortaroj, &QTreeWidget::itemActivated, [this](QTreeWidgetItem* vico)
    {
        agorduĈuWortaroEstasElektitan(vico->text(1), Linguo(vico->text(0)), veran);
    });
}

Nenio MenuoDeWortaresLinguoj::agorduElekteblajnWortarojn(InformoDeWortaroj p_wortaroj)
{
    wortaroj = formovu(p_wortaroj);
    ĉuMontrasFonton = wortaroj.grupoj.grandon() > 1;
    kreuListonDeWortaroj();
    
    for (ℕ i = 0; i < elektitajWortaroj.grandon();)
    {
        InformoDeWortaroj::Grupo* grupo = wortaroj.provuTrovi(elektitajWortaroj[i].first);
        
        if (grupo == nullptr aŭ grupo->provuTrovi(elektitajWortaroj[i].second) == nullptr)
        {
            kiamOniMalelektisWortaron(elektitajWortaroj[i].first, elektitajWortaroj[i].second);
            elektitajWortaroj.forprenu(i);
        }
        else i++;
    }
    
    for (const Paro<Texto, Linguo>& elektitaWortaro : elektitajWortaroj)
        markuWortaron(elektitaWortaro.first, elektitaWortaro.second, veran);
}

Nenio MenuoDeWortaresLinguoj::agorduĈuWortaroEstasElektitan
        (const Texto& fonto, const Linguo& linguo, Buleo ĉuEstasElektitan)
{
    Paro<Texto, Linguo> novaParo(fonto, linguo);
    
    if (ĉuEstasElektitan == elektitajWortaroj.ĉuEnhavas(novaParo))
        eligu;
    
    if (ĉuEstasElektitan)
        elektitajWortaroj.enmetu(formovu(novaParo));
    else elektitajWortaroj.forprenuĈiun(novaParo);
    
    markuWortaron(fonto, linguo, ĉuEstasElektitan);
    kreuListonDeElektitajWortaroj();
    
    if (ĉuEstasElektitan)
        kiamOniElektisNovanWortaron(fonto, linguo);
    else kiamOniMalelektisWortaron(fonto, linguo);
    
    rekreuAranĝon();
}

Nenio MenuoDeWortaresLinguoj::agorduLinguonDeFasado(Linguo linguo)
{
    linguoDeFasado = linguo;
    kreuListonDeElektitajWortaroj();
    kreuListonDeWortaroj();
    rekreuAranĝon();
}

Nenio MenuoDeWortaresLinguoj::preparuTextojn()
{
    kapo->setText(tr("Wortaroj"));
}

Nenio MenuoDeWortaresLinguoj::rekreuAranĝon()
{
    AranĝantoKunAnimacioj::Aranĝo aranĝo;
    ℤ altoDeElektitajWortaroj = 0;
    if (ne elektitajWortaroj.ĉuEstasMalplenan())
    {
        ℕ altoDeVico = fElektitajWortaroj->sizeHintForRow(0);
        altoDeElektitajWortaroj = elektitajWortaroj.grandon() * altoDeVico + 4;
        if (height() > 100)
            altoDeElektitajWortaroj = std::min(height() / 3, altoDeElektitajWortaroj);
    }
    
    ℤ altoDeInformujo = 0;
    if (ne informujo->document()->isEmpty())
        altoDeInformujo = informujo->document()->size().height() + 4;
    
    aranĝo.anoj.enmetuNovan(kapo, 0, 0, 1, 0, 0, 0, 0, kapo->sizeHint().height());
    ℤ y = kapo->sizeHint().height();
    aranĝo.anoj.enmetuNovan(informujo, 0, 0, 1, 0, 0, y, 0, altoDeInformujo);
    y += altoDeInformujo;
    aranĝo.anoj.enmetuNovan(fElektitajWortaroj, 0, 0, 1, 0, 0, y, 0, altoDeElektitajWortaroj);
    y += altoDeElektitajWortaroj;
    aranĝo.anoj.enmetuNovan(fWortaroj, 0, 0, 1, 1, 0, y, 0, -y);
    
    aranĝanto->agorduAranĝonRulante(aranĝo);
}

Nenio MenuoDeWortaresLinguoj::kreuListonDeWortaroj()
{
    fWortaroj->clear();
    fWortaroj->setSortingEnabled(malveran);
    
    fWortaroj->setColumnCount(5);
    fWortaroj->setHeaderItem(kreu QTreeWidgetItem((QTreeWidget*) nullptr, {"", "", tr("linguo"), "", tr("wortoj")}));
    
    for (const InformoDeWortaroj::Grupo& grupo : wortaroj.grupoj)
    {
        for (const InformoDeWortaroj::Wortaro& wortaro : grupo.wortaroj)
        {
            QTreeWidgetItem* ano = kreu QTreeWidgetItem(fWortaroj, {wortaro.linguo.iso639_3.QT(),
                                                                    grupo.fonto.QT(),
                                                                    wortaro.linguo.donuNomon(linguoDeFasado).QT(),
                                                                    grupo.mallongaNomo.QT(),
                                                                    ""});
            ano->setData(4, Qt::DisplayRole, wortaro.nombroDaWortoj);
        }
    }
    
    fWortaroj->hideColumn(1);
    fWortaroj->sortByColumn(4, Qt::DescendingOrder);
    fWortaroj->setSortingEnabled(veran);
    
    if (ĉuMontrasFonton)
        fWortaroj->showColumn(3);
    else
        fWortaroj->hideColumn(3);
    
    regrandiguKolumnojnDeTabeloDeWortaroj();
}

Nenio MenuoDeWortaresLinguoj::kreuListonDeElektitajWortaroj()
{
    fElektitajWortaroj->clear();
    fElektitajWortaroj->setSortingEnabled(malveran);
    
    fElektitajWortaroj->setColumnCount(3);
    fElektitajWortaroj->setHeaderHidden(veran);
    
    for (const Paro<Texto, Linguo>& wortaro : elektitajWortaroj)
        kreu QTreeWidgetItem(fElektitajWortaroj, {wortaro.second.donuNomon(linguoDeFasado).QT(),
                                                  wortaro.first.QT(),
                                                  wortaro.second.iso639_3.QT()});
    
    if (ĉuMontrasFonton)
        fElektitajWortaroj->showColumn(1);
    else
        fElektitajWortaroj->hideColumn(1);
    
    fElektitajWortaroj->hideColumn(2);
    fElektitajWortaroj->sortByColumn(0, Qt::AscendingOrder);
    fElektitajWortaroj->setSortingEnabled(veran);
}

Nenio MenuoDeWortaresLinguoj::markuWortaron(const Texto& fonto, const Linguo& linguo, Buleo ĉuEstasMarkitan)
{
    QList<QTreeWidgetItem*> rezulto = fWortaroj->findItems(linguo.iso639_3.QT(), Qt::MatchExactly, 0);
    
    for (ℕ i = 0; i < rezulto.size();)
        if (rezulto[i]->text(1) != fonto.QT())
            rezulto.removeAt(i);
        else i++;
    
    for (QTreeWidgetItem* ano : rezulto)
        markuAnon(ano, ĉuEstasMarkitan);
}

Nenio MenuoDeWortaresLinguoj::markuAnon(QTreeWidgetItem* ano, Buleo ĉuEstasMarkitan) const
{
    for (ℕ i = 0; i < ano->columnCount(); i++)
    {
        ano->setForeground(i, ĉuEstasMarkitan ? elektita_textkoloro : fWortaroj->palette().foreground());
        ano->setBackground(i, ĉuEstasMarkitan ? elektita_fonkoloro : fWortaroj->palette().background());
    }
}

Nenio MenuoDeWortaresLinguoj::montruPriskribonDeWortaro(const Texto& fonto, const Linguo& linguo)
{
    InformoDeWortaroj::Grupo* grupo = wortaroj.provuTrovi(fonto);
    if (grupo == nullptr)
        eligu;
    InformoDeWortaroj::Wortaro* wortaro = grupo->provuTrovi(linguo);
    if (wortaro == nullptr)
        eligu;
    
    QString html = tr("<center><p>%1 el %2</p></center>").arg(wortaro->linguo.donuNomon(linguoDeFasado).QT()).arg(grupo->fonto.QT());
    if (ne grupo->leĝaInformo.ĉuEstasMalplenan())
        html += "<p>" + grupo->leĝaInformo.QT() + "</p>";
    
    informujo->setHtml(html);
    rekreuAranĝon();
}

Nenio MenuoDeWortaresLinguoj::regrandiguKolumnojnDeTabeloDeWortaroj()
{
    static constexpr ℤ larĝo_kodo = 50;
    static constexpr ℤ larĝo_fonto = 35;
    static constexpr ℤ larĝo_wortoj = 60;
    ℕ larĝoDeWidget = fWortaroj->width() == 0 ? 400 : fWortaroj->width();
    ℤ larĝo_linguo = larĝoDeWidget - larĝo_kodo - larĝo_wortoj - 20;
    if (ĉuMontrasFonton)
        larĝo_linguo -= larĝo_fonto;
    
    fWortaroj->setColumnWidth(0, larĝo_kodo);
    fWortaroj->setColumnWidth(2, larĝo_linguo);
    fWortaroj->setColumnWidth(3, larĝo_fonto);
    fWortaroj->setColumnWidth(4, larĝo_wortoj);
}