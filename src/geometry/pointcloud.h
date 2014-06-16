#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "geometry.h"
#include "oivec.h"

class PointCloud : public Geometry
{
    Q_OBJECT
public:
    PointCloud(bool isNominal, QObject *parent = 0);
    PointCloud(const PointCloud &copy);
    ~PointCloud();

    OiVec xyz;
    QList<OiVec> points;

    void recalc();

    bool toOpenIndyXML(QXmlStreamWriter& stream);
    ElementDependencies fromOpenIndyXML(QXmlStreamReader& xml);

    QString getX();
    QString getY();
    QString getZ();
    QString getIsCommon();
    QString getIsNominal();
};

#endif // POINTCLOUD_H
