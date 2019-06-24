#include "OpenDriveParser.h"

OpenDriveParser::OpenDriveParser()
{
}

OpenDriveParser::~OpenDriveParser()
{
}

bool OpenDriveParser::xmlStreamReaderFile(const QString fileName)
{
    if(fileName.isEmpty() || fileName.length()==0)
    {
        qDebug()<<"Error : FileName Error.";
        return false;
    }

    QFile file(fileName);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        qDebug()<<"Error : can't read file."<<qPrintable(fileName)<<":"
               <<qPrintable(file.errorString());
        return false;
    }

    qDebug()<<"=====parse start=====";
    QXmlStreamReader reader;
    reader.setDevice(&file);//根节点

    while(!reader.atEnd())
    {
        //读取下一个元素
        QXmlStreamReader::TokenType nType = reader.readNext();
        switch (nType)
        {
            // 开始文档
            case QXmlStreamReader::StartDocument:
            {
                qDebug() << QString::fromLocal8Bit("***开始文档（XML 声明*** ");
                // XML 声明
                QString strVersion = reader.documentVersion().toString();
                QString strEncoding = reader.documentEncoding().toString();
                bool bAlone = reader.isStandaloneDocument();
                qDebug() << QString::fromLocal8Bit("版本：%1  编码：%2  Standalone：%3").arg(strVersion).arg(strEncoding).arg(bAlone)
                         << endl;
                break;
            }

            //开始元素
            case QXmlStreamReader::StartElement:
            { // 开始元素
                QString strElementName = reader.name().toString();
                if (QString::compare(strElementName, "OpenDRIVE") == 0)
                {
                    // 根元素
                    qDebug() << QString::fromLocal8Bit("具备OpenDRIVE节点,开始解析")<<endl;
                    parseOpenDrive(&reader);
                }
                else
                {
                    qDebug() <<"File Error : Not A OpenDrive File"<<endl;
                    return false;
                }
                break;
            }
        }
    file.close();
    return true;
    }
}


bool OpenDriveParser::parseOpenDrive(QXmlStreamReader* reader)
{
    //读取下一个元素
    QXmlStreamReader::TokenType nType = reader.readNext();
    while(!reader.atEnd())
    {
        if (nType == QXmlStreamReader::StartElement)
        {
            if (reader.name().toString() == "header")
            {
                parseHeader(&reader);
            }
            else if (reader.name().toString() == "road")
            {

            }
            else if (reader.name().toString() == "junction")
            {

            }
        }
    }


}

bool OpenDriveParser::parseHeader(QXmlStreamReader* reader)
{
    QXmlStreamAttributes attributes = reader.attributes();
    if (attributes.hasAttribute("revMajor"))
    {
        QString revMajor = attributes.value("revMajor").toString();
        qDebug() << QString::fromLocal8Bit("属性：revMajor(%1)").arg(revMajor);
        return true;
    }

        return false;

}
