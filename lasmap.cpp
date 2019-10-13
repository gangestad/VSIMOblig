#include "lasmap.h"
#include "math_constants.h"
#include "vertex.h"
#include <QDebug>
#include <cmath>
#include <algorithm>

LasMap::LasMap()
{
//    Vertex v{};
//    v.set_xyz(0, 0, 0);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(0, 0);
//    mVertices.push_back(v);
//    v.set_xyz(2, 0, 0);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(1, 0);
//    mVertices.push_back(v);
//    v.set_xyz(2, 0, 2);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(1, 1);
//    mVertices.push_back(v);
//    v.set_xyz(0, 0, 0);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(0, 0);
//    mVertices.push_back(v);
//    v.set_xyz(2, 0, 2);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(1, 1);
//    mVertices.push_back(v);
//    v.set_xyz(0, 0, 2);
//    v.set_rgb(0, 1, 0);
//    v.set_uv(0, 1);
//    mVertices.push_back(v);

    //printSomePoints();   
    readFile("../VSIMOblig/LASdata/33-1-497-327-20.txt");
    addAllPointsToVertices();
    centerMap();

}

LasMap::~LasMap()
{

}

void LasMap::init()
{
    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // 3rd attribute buffer : uvs
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glPointSize(2.f);

    glBindVertexArray(0);
}

void LasMap::draw()
{
    glBindVertexArray(mVAO);
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}

void LasMap::printSomePoints()
{
    for (auto point = lasloader.begin() + 10; point != lasloader.end() - 25; ++point)
    {
        std::cout << "Point: (" << point->xNorm() << ", " << point->yNorm() << ", " << point->zNorm() << ")" << std::endl;
    }
}

void LasMap::addAllPointsToVertices()
{
    mVertices.clear();
    for (auto point : points)
    {
            Vertex v{};
//            v.set_xyz(point.xNorm(), point.yNorm(), point.zNorm());
            v.set_xyz(point.x, point.z, point.y);
            v.set_rgb(0, 1, 0);
            v.set_uv(0, 0);
            mVertices.push_back(v);
    }

//    int i = 0;
//    for (auto point : lasloader)
//    {
//        ++i;
//    }
//    std::cout << i << "\n";



//    for (auto point : points)
//    {
//            Vertex v{};
//            v.set_xyz(point.getX(), point.getY(), point.getZ());
//            v.set_rgb(0, 1, 0);
//            v.set_uv(0, 0);
//            mVertices.push_back(v);
//    }
}

void LasMap::centerMap()
{
    std::vector<float> xValues;
    std::vector<float> zValues;
    std::vector<float> yValues;


        for (auto point : lasloader)
    {
        xValues.push_back(point.x);
        yValues.push_back(point.z);
        zValues.push_back(point.y);



//        xValues.push_back(point.xNorm());
//        yValues.push_back(point.yNorm());
//        zValues.push_back(point.zNorm());
    }
    std::sort(xValues.begin(), xValues.end());
    std::sort(zValues.begin(), zValues.end());
    std::sort(yValues.begin(), yValues.end());

//    std::cout << xValues[0] << " ";
//    std::cout << yValues[0] << " ";
//    std::cout << zValues[0] << " ";

//    std::cout << xValues[xValues.size() - 1] << " ";
//    std::cout << yValues[yValues.size() - 1] << " ";
//    std::cout << zValues[zValues.size() - 1] << " ";

//    double xTranslate = (-xValues[0] + xValues[xValues.size() - 1]) ;
//    double yTranslate = (-yValues[0] + yValues[xValues.size() - 1]) ;
//    double zTranslate = (-zValues[0] + zValues[xValues.size() - 1]) ;

    double xTranslate = ((xValues[xValues.size() - 1]) - ((xValues[xValues.size() - 1] - xValues[0]) * 0.5));
    double yTranslate = ((zValues[xValues.size() - 1]) - ((zValues[xValues.size() - 1] - zValues[0]) * 0.5));
    double zTranslate = ((yValues[xValues.size() - 1]) - ((yValues[xValues.size() - 1] - yValues[0]) * 0.5));

    double scaleNumber = 1;
    scale(scaleNumber);
    move(gsl::Vector3D(-xTranslate * scaleNumber, -zTranslate * scaleNumber, -yTranslate * scaleNumber));
    //mMatrix.translate(-xTranslate, -yTranslate, -zTranslate);
    //mMatrix.translate(2, 2, 2);


    ////    move(gsl::Vector3D(-483197.75, -7569861.26, 0.70));
}

void LasMap::readFile()
{
//    LASreadOpener lasreadopener;
//    lasreadopener.set_file_name("../VSIMOblig/LASdata/33-1-497-327-20.las");
//    LASreader* lasreader = lasreadopener.open();

//    while (lasreader->read_point())
//    {
//        Vertex v{};
////            v.set_xyz(point.xNorm(), point.yNorm(), point.zNorm());
//        v.set_xyz(lasreader->get_x(), lasreader->get_y(), lasreader->get_z());
//        v.set_rgb(0, 1, 0);
//        v.set_uv(0, 0);
//        mVertices.push_back(v);
//    }

}

void LasMap::readFile(std::string filename)
{
    std::ifstream inn;

    inn.open(filename);

    if (inn.is_open())
    {
        unsigned int n;
        gsl::Vector3D vertex;
        inn >> n;
        points.reserve(n);
        for (unsigned int i = 0; i < n; i++)
        {
            inn >> vertex;
            points.push_back(vertex);

            std::string str;
            std::getline(inn, str);
        }
        inn.close();
        //qDebug() << "TriangleSurface file read: " << QString::fromStdString(filename);
    }
    else
    {
        //qDebug() << "Could not open file for reading: " << QString::fromStdString(filename);
    }

    for (int i = 0; i < 30; ++i)
    {
        std::cout << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
    }
    std::cout << std::setprecision(10) << points.size() << "\n";
}


