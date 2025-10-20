#include "KnowledgeBase.h"
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

KnowledgeBase::KnowledgeBase(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadKnowledgeData();
    populateTopicList();
}

void KnowledgeBase::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title with terminal styling
    QLabel *headerLabel = new QLabel(">>> [BASE_DE_CONOCIMIENTO_TARDIGRADOS] <<<", this);
    headerLabel->setStyleSheet(
        "QLabel { "
        "font-size: 18px; "
        "font-weight: bold; "
        "color: #00ff41; "
        "padding: 10px; "
        "background-color: #000000; "
        "border: 2px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "}"
    );
    headerLabel->setAlignment(Qt::AlignCenter);
    
    mainLayout->addWidget(headerLabel);
    
    // Create splitter
    mainSplitter = new QSplitter(Qt::Horizontal, this);
    
    // Topic list with terminal styling
    topicList = new QListWidget();
    topicList->setMaximumWidth(250);
    topicList->setStyleSheet(
        "QListWidget { "
        "background-color: #000000; "
        "border: 2px solid #00ff00; "
        "color: #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "}"
        "QListWidget::item { "
        "padding: 8px; "
        "border-bottom: 1px solid #003300; "
        "color: #00ff00; "
        "}"
        "QListWidget::item:selected { "
        "background-color: #003300; "
        "color: #00ff41; "
        "border: 1px solid #00ff41; "
        "}"
        "QListWidget::item:hover { "
        "background-color: #001100; "
        "color: #00ff88; "
        "}"
    );
    
    // Content area with terminal styling
    QWidget *contentWidget = new QWidget();
    contentWidget->setStyleSheet("QWidget { background-color: #000000; }");
    QVBoxLayout *contentLayout = new QVBoxLayout(contentWidget);
    
    titleLabel = new QLabel(">>> [SELECCIONA_UN_TEMA] <<<");
    titleLabel->setStyleSheet(
        "QLabel { "
        "font-size: 16px; "
        "font-weight: bold; "
        "color: #00ff41; "
        "padding: 10px; "
        "background-color: #000000; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "}"
    );
    titleLabel->setAlignment(Qt::AlignCenter);
    
    contentArea = new QTextEdit();
    contentArea->setReadOnly(true);
    contentArea->setStyleSheet(
        "QTextEdit { "
        "background-color: #000000; "
        "color: #00ff00; "
        "border: 2px solid #00ff00; "
        "padding: 10px; "
        "font-family: 'Courier New', monospace; "
        "font-size: 12px; "
        "line-height: 1.4; "
        "}"
        "QScrollBar:vertical { "
        "background-color: #000000; "
        "border: 1px solid #00ff00; "
        "width: 15px; "
        "}"
        "QScrollBar::handle:vertical { "
        "background-color: #00ff00; "
        "border: 1px solid #00ff41; "
        "min-height: 20px; "
        "}"
        "QScrollBar::handle:vertical:hover { "
        "background-color: #00ff41; "
        "}"
    );
    
    contentLayout->addWidget(titleLabel);
    contentLayout->addWidget(contentArea);
    
    // Add widgets to splitter
    mainSplitter->addWidget(topicList);
    mainSplitter->addWidget(contentWidget);
    mainSplitter->setStretchFactor(0, 0);  // Topic list doesn't stretch
    mainSplitter->setStretchFactor(1, 1);  // Content area stretches
    
    mainLayout->addWidget(mainSplitter);
    
    // Connect signals
    connect(topicList, &QListWidget::currentRowChanged, this, &KnowledgeBase::onTopicSelected);
}

void KnowledgeBase::loadKnowledgeData()
{
    // Create knowledge data with terminal styling
    QJsonObject anatomia;
    anatomia["title"] = ">>> [ANATOMIA_DE_TARDIGRADOS] <<<";
    anatomia["content"] = 
        "<h3 style='color: #00ff41; font-family: Courier New, monospace;'>>>> ESTRUCTURA_CORPORAL <<<<</h3>"
        "<p style='color: #00ff00; font-family: Courier New, monospace;'>Los tardígrados son microorganismos de 0.05 a 1.5 mm de longitud, con un cuerpo segmentado "
        "dividido en cabeza y cuatro segmentos corporales, cada uno con un par de patas terminadas in garras.</p>"
        
        "<h3>Características Principales</h3>"
        "<ul>"
        "<li><strong>Cutícula:</strong> Cubierta externa flexible que permite la deshidratación</li>"
        "<li><strong>Sistema digestivo:</strong> Boca con estilete para perforar células vegetales</li>"
        "<li><strong>Músculos:</strong> Sistema muscular simple pero efectivo</li>"
        "<li><strong>Sistema nervioso:</strong> Ganglio cerebral y cordones nerviosos</li>"
        "</ul>"
        
        "<h3>Adaptaciones Especiales</h3>"
        "<p>Su anatomía está adaptada para la supervivencia extrema, incluyendo proteínas especiales "
        "que protegen las estructuras celulares durante la criptobiosis.</p>";
    
    QJsonObject habitat;
    habitat["title"] = "🌍 Hábitats Naturales";
    habitat["content"] = 
        "<h3>Distribución Global</h3>"
        "<p>Los tardígrados se encuentran en prácticamente todos los hábitats del planeta, desde "
        "los océanos más profundos hasta las montañas más altas.</p>"
        
        "<h3>Ambientes Típicos</h3>"
        "<ul>"
        "<li><strong>Musgos y líquenes:</strong> Su hábitat más común</li>"
        "<li><strong>Sedimentos marinos:</strong> Desde la costa hasta las fosas abisales</li>"
        "<li><strong>Agua dulce:</strong> Lagos, ríos y charcos temporales</li>"
        "<li><strong>Suelos:</strong> En la humedad entre partículas de tierra</li>"
        "<li><strong>Ambientes extremos:</strong> Desiertos, glaciares, fuentes termales</li>"
        "</ul>"
        
        "<h3>Condiciones de Vida</h3>"
        "<p>Prefieren ambientes húmedos pero pueden sobrevivir en condiciones extremadamente secas "
        "entrando en estado de criptobiosis.</p>";
    
    QJsonObject resistencia;
    resistencia["title"] = "💪 Capacidades de Resistencia";
    resistencia["content"] = 
        "<h3>Tolerancia a Temperaturas Extremas</h3>"
        "<ul>"
        "<li><strong>Calor:</strong> Hasta 150°C por períodos cortos</li>"
        "<li><strong>Frío:</strong> Pueden sobrevivir a -272°C (cerca del cero absoluto)</li>"
        "<li><strong>Congelación:</strong> Resistentes a múltiples ciclos de congelación-descongelación</li>"
        "</ul>"
        
        "<h3>Resistencia a la Radiación</h3>"
        "<p>Pueden soportar hasta 5,000 Gy de radiación (1,000 veces más que los humanos), "
        "gracias a mecanismos eficientes de reparación del ADN.</p>"
        
        "<h3>Supervivencia en el Vacío</h3>"
        "<p>Han sobrevivido exposiciones al espacio exterior, resistiendo la radiación cósmica, "
        "rayos UV extremos y el vacío absoluto.</p>"
        
        "<h3>Presiones Extremas</h3>"
        "<p>Toleran presiones desde el vacío hasta 6,000 atmósferas (6 veces más que en la fosa más profunda).</p>";
    
    QJsonObject criptobiosis;
    criptobiosis["title"] = "😴 Criptobiosis (Estado Tun)";
    criptobiosis["content"] = 
        "<h3>¿Qué es la Criptobiosis?</h3>"
        "<p>Es un estado de latencia donde los procesos metabólicos se detienen casi completamente, "
        "permitiendo supervivencia a largo plazo en condiciones extremas.</p>"
        
        "<h3>Tipos de Criptobiosis</h3>"
        "<ul>"
        "<li><strong>Anhidrobiosis:</strong> Supervivencia a la deshidratación extrema</li>"
        "<li><strong>Criobiosis:</strong> Supervivencia a temperaturas bajo cero</li>"
        "<li><strong>Osmobiosis:</strong> Supervivencia a cambios de salinidad</li>"
        "<li><strong>Anoximbiosis:</strong> Supervivencia sin oxígeno</li>"
        "</ul>"
        
        "<h3>Mecanismos Moleculares</h3>"
        "<p>Durante la criptobiosis, los tardígrados producen:</p>"
        "<ul>"
        "<li><strong>Trehalosa:</strong> Azúcar que protege las membranas celulares</li>"
        "<li><strong>Proteínas TDPs:</strong> Reemplazan el agua y estabilizan las estructuras</li>"
        "<li><strong>Antioxidantes:</strong> Protegen contra el daño oxidativo</li>"
        "</ul>"
        
        "<h3>Revivificación</h3>"
        "<p>Cuando las condiciones mejoran, pueden revivir completamente en minutos u horas, "
        "reanudando todas sus funciones vitales normales.</p>";
    
    QJsonObject ciclo;
    ciclo["title"] = "🔄 Ciclo de Vida";
    ciclo["content"] = 
        "<h3>Reproducción</h3>"
        "<p>Los tardígrados pueden reproducirse de forma sexual o asexual (partenogénesis), "
        "dependiendo de las condiciones ambientales.</p>"
        
        "<h3>Desarrollo</h3>"
        "<ol>"
        "<li><strong>Huevo:</strong> Resistente a condiciones extremas</li>"
        "<li><strong>Juveniles:</strong> 4 estados juveniles con mudas</li>"
        "<li><strong>Adulto:</strong> Capaz de reproducción</li>"
        "</ol>"
        
        "<h3>Longevidad</h3>"
        "<ul>"
        "<li><strong>Vida activa:</strong> 2-3 meses en condiciones normales</li>"
        "<li><strong>En criptobiosis:</strong> Décadas o incluso siglos</li>"
        "<li><strong>Récord:</strong> Revivals después de 30+ años en estado tun</li>"
        "</ul>"
        
        "<h3>Muda</h3>"
        "<p>Como otros invertebrados, mudan su cutícula durante el crecimiento, "
        "un proceso que también pueden hacer durante la criptobiosis.</p>";
    
    QJsonObject importancia;
    importancia["title"] = "🚀 Importancia Científica";
    importancia["content"] = 
        "<h3>Investigación Biomédica</h3>"
        "<ul>"
        "<li><strong>Medicina espacial:</strong> Modelos para viajes interplanetarios</li>"
        "<li><strong>Conservación:</strong> Técnicas de preservación criogénica</li>"
        "<li><strong>Longevidad:</strong> Estudio del envejecimiento y la reparación celular</li>"
        "</ul>"
        
        "<h3>Biotecnología</h3>"
        "<ul>"
        "<li><strong>Biomateriales:</strong> Desarrollo de materiales resistentes</li>"
        "<li><strong>Farmacología:</strong> Compuestos protectores naturales</li>"
        "<li><strong>Nanotecnología:</strong> Aplicaciones a escala microscópica</li>"
        "</ul>"
        
        "<h3>Astrobiología</h3>"
        "<p>Los tardígrados son organismos modelo para estudiar la posibilidad de vida "
        "en otros planetas y la panspermia (transferencia de vida entre planetas).</p>"
        
        "<h3>Educación</h3>"
        "<p>Son excelentes para enseñar conceptos de:</p>"
        "<ul>"
        "<li>Adaptación evolutiva</li>"
        "<li>Extremófilos</li>"
        "<li>Biología molecular</li>"
        "<li>Supervivencia celular</li>"
        "</ul>";
    
    // Add all topics to knowledge data
    knowledgeData["anatomia"] = anatomia;
    knowledgeData["habitat"] = habitat;
    knowledgeData["resistencia"] = resistencia;
    knowledgeData["criptobiosis"] = criptobiosis;
    knowledgeData["ciclo"] = ciclo;
    knowledgeData["importancia"] = importancia;
    
    topicKeys << "anatomia" << "habitat" << "resistencia" << "criptobiosis" << "ciclo" << "importancia";
}

void KnowledgeBase::populateTopicList()
{
    topicList->clear();
    
    for (const QString &key : topicKeys) {
        QJsonObject topic = knowledgeData[key].toObject();
        topicList->addItem(topic["title"].toString());
    }
    
    // Select first item by default
    if (topicList->count() > 0) {
        topicList->setCurrentRow(0);
    }
}

void KnowledgeBase::onTopicSelected(int currentRow)
{
    if (currentRow >= 0 && currentRow < topicKeys.size()) {
        QString key = topicKeys[currentRow];
        displayTopicContent(key);
    }
}

void KnowledgeBase::displayTopicContent(const QString &topic)
{
    QJsonObject topicObj = knowledgeData[topic].toObject();
    
    titleLabel->setText(topicObj["title"].toString());
    contentArea->setHtml(topicObj["content"].toString());
}