#ifndef MXMLSTREAMREADER_H
#define MXMLSTREAMREADER_H
#include<QXmlStreamReader>
#include<vector>
#include<list>


class MXmlStreamReader
{
public:
    MXmlStreamReader();
    bool readFile(const QString &fileName);

private:
    void readHeaderElement();
    void readRoadElement();
    void readJunctionlement();

    QXmlStreamReader reader;


};

#endif // MXMLSTREAMREADER_H
