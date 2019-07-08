#include "CustomPlot.h"

CustomPlot::CustomPlot(QCustomPlot* qCustomPlot)
{
    plot = qCustomPlot;
    mOpenDriveParser.mOpenDriveStruct = &mOpenDriveStruct;
    string fileName = "/home/pz1_ad_04/qtcreater/source/RealMap2.xml";
    //string fileName = "/home/pz1_ad_04/qtcreater/pathPlan3/RealMap2.xml";
    mOpenDriveParser.ReadFile(fileName);
}

CustomPlot::~CustomPlot(){

}

void CustomPlot::initPlot()
{
//    lsNone        ///< data points are not connected with any lines (e.g. data only represented
//                                     ///< with symbols according to the scatter style, see \ref setScatterStyle)
//                       ,lsLine       ///< data points are connected by a straight line
//                       ,lsStepLeft   ///< line is drawn as steps where the step height is the value of the left data point
//                       ,lsStepRight  ///< line is drawn as steps where the step height is the value of the right data point
//                       ,lsStepCenter ///< line is drawn as steps where the step is in between two data points
//                       ,lsImpulse
    //地图绘制
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::black));
    //plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    plot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    plot->graph(0)->rescaleAxes();
    //目标点
    plot->addGraph();
    plot->graph(1)->setPen(QPen(Qt::blue));
    //plot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    plot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    plot->graph(1)->rescaleAxes();
    //实时GPS点转笛卡尔坐标
    plot->addGraph();
    plot->graph(2)->setPen(QPen(Qt::red));
    //plot->graph(2)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(2)->setLineStyle(QCPGraph::lsNone);
    plot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    plot->graph(2)->rescaleAxes();
    //行驶轨迹轨迹
    plot->addGraph();
    plot->graph(3)->setPen(QPen(Qt::green));
    //plot->graph(3)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    plot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    plot->graph(3)->rescaleAxes();

    plot->axisRect()->setupFullAxesBox(true);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //plot->graph(0)->rescaleAxes(true);
    plot->xAxis->setRange(-400,100);
    plot->yAxis->setRange(-150,50);
}

void CustomPlot::plotMap(){
    QCustomPlot* mapView = plot;
    vector<RoadNet>* mRoadNetVector = &mOpenDriveStruct.mRoadNetVector;
    int RoadNetNum = mRoadNetVector->size();
    int i;
    for(i=0;i<RoadNetNum;i++){
        vector<GeoObj>* mGeos;
        mGeos = &mRoadNetVector->at(i).Geos;
        int mGeoslength = mGeos->size();
        double RoadGeoEnd = mGeos->at(mGeoslength-1).s + mGeos->at(mGeoslength-1).length;
        //打印参考线
        for(int j =0;j<mGeoslength;j++){
            plotGeo(&mGeos->at(j),i);
        }
        //打印车道线
        vector<offsetObj>* mOffsets;
        mOffsets = &mRoadNetVector->at(i).Offsets;
        //统计需要显示的车道，并剔除重复元素，这里使用set
        set<int> laneId;
        int mOffsetsLength = mOffsets->size();
        for (int m=0;m<mOffsetsLength;m++) {
            string s1 = mOffsets->at(m).type;
            string s2 = "driving";
            if (s1.compare(s2) == 0)
                laneId.insert(mOffsets->at(m).id);
        }

        for (int n=0;n<mGeoslength;n++) {
            for(set<int>::iterator it = laneId.begin(); it != laneId.end(); it++){
                plotLane(i,n,*it);
            }

        }


    }


}

//打印参考线
void  CustomPlot::plotGeo(GeoObj* mObj,int RoadIdx){
    QCustomPlot* mapView = plot;
    vector<RoadNet>* mRoadNetVector = &mOpenDriveStruct.mRoadNetVector;
    double delta_s = 0.5;
    int N = floor(mObj->length/delta_s);
    QVector<double> X;
    QVector<double> Y;
    double sValueset[N];
    double data[3]={0} ;
    for (int var = 0; var < N; ++var) {
        sValueset[var] = mObj->s + delta_s *var;
        mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
        double x = data[0];
        double y = data[1];
        //double hdg = data[2];
        X.append(x);
        Y.append(y);
    }
    plotPointInMap(X,Y);


}

//打印车道线
 void CustomPlot::plotLane(int RoadIdx,int GeoId,int id)
 {
     QCustomPlot* mapView = plot;
     vector<RoadNet>* mRoadNetVector = &mOpenDriveStruct.mRoadNetVector;
     double delta_s =0.5;
     int N = floor(mRoadNetVector->at(RoadIdx).Geos.at(GeoId).length/delta_s);
     QVector<double> X;
     QVector<double> Y;

     double sValueset[N];
     double data[3]={0} ;

     for (int var = 0; var < N; ++var) {
         sValueset[var] = mRoadNetVector->at(RoadIdx).Geos.at(GeoId).s + delta_s *var;
         mOpenDriveStruct.GetXYHdgByS(mRoadNetVector,RoadIdx,sValueset[var], data);
         double x = data[0];
         double y = data[1];
         double hdg = data[2];
         double offset = mOpenDriveStruct.GetSOffset(sValueset[var],id,mRoadNetVector,RoadIdx);
         x = x + offset*cos(hdg + sign(id)*M_PI/2);
         y = y + offset*sin(hdg + sign(id)*M_PI/2);
         X.append(x);
         Y.append(y);
     }
    plotPointInMap(X,Y);
 }


void CustomPlot::plotPointInMap(const QVector<double> x,const QVector<double> y)
{
    //设置画笔
    QPen pen;
    pen.setColor(Qt::blue);
    //add Gragh
    QCPGraph* currentGragh = NULL;
    currentGragh = plot->addGraph();
    currentGragh->setPen(pen);
    currentGragh->rescaleAxes(true);//自动调整轴上值的范围
    currentGragh->setData(x,y);//设置数据
//    plot->graph(0)->setData(x,y);
//    plot->replot();

}
