#include "MXmlStreamReader.h"

MXmlStreamReader::MXmlStreamReader()
{

}

bool MXmlStreamReader::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug()<<"Open XML file Error";
        return false;
    }

    reader.setDevice(&file);//关联IODevice
    reader.readNext();//header节点
    while(!reader.atEnd())
    {
        if(reader.isStartElement())
        {
            if(reader.name() == "header")
            {
                readHeaderElement(reader);
            }
            else if(reader.name() == "road")
            {
                readRoadElement();
            }
            else if(reader.name() == "junction")
            {
                readJunctionlement();
            }

        }
    }
    file.close();
    if(reader.hasError())
    {
        qDebug()<<reader.errorString();
        return false;
    }
    else if(file.error() != QFile::NoError)
    {
        qDebug()<<file.errorString();
        return false;
    }

    return true;
}

void MXmlStreamReader::readHeaderElement(QXmlStreamReader &reader)
{
    QXmlStreamAttributes HeaderAttrs = reader.attributes();
}


void MXmlStreamReader::readRoadElement()
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if(reader.isStartElement())
        {
            if(reader.name() == "entry")
            {
                readEntryElement(treeWidget->invisibleRootItem());
            }
            else
            {
                skipUnknownElement();
            }
        }
        else
        {
            reader.readNext();
        }
    }
}

void MXmlStreamReader::readEntryElement(QTreeWidgetItem *parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0,reader.attributes().value("term").toString());
    item->setText(2,reader.attributes().value("description").toString());
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if(reader.isStartElement())
        {
            if(reader.name() == "entry")
            {
                readEntryElement(item);
            }
            else if(reader.name() == "page")
            {
                readPageElement(item);
            }
        }
        else
        {
            reader.readNext();
        }
    }
}

void MXmlStreamReader::readPageElement(QTreeWidgetItem *parent)
{
    QString page = reader.readElementText();
    if(reader.isEndElement())
        reader.readNext();

    QString allPages = parent->text(1);
    if(!allPages.isEmpty())
        allPages +=", ";
    allPages += page;
    parent->setText(1,allPages);
}

void MXmlStreamReader::skipUnknownElement()
{
    reader.readNext();
    while(!reader.atEnd())
    {
        if(reader.isEndElement())
        {
            reader.readNext();
            break;
        }

        if(reader.isStartElement())
        {
            skipUnknownElement();
        }
        else
        {
            reader.readNext();
        }
    }
}
