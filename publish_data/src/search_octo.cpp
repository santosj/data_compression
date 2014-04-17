#include <ros/ros.h>
#include <octomap/octomap.h>
#include <octomap_msgs/Octomap.h>
#include <geometry_msgs/Point.h>
#include <octomap_msgs/conversions.h>
#include <octomap/AbstractOccupancyOcTree.h>

using namespace octomap;


void octobinCallback(const octomap_msgs::Octomap::ConstPtr& msg)
{
    double x, y, z, r;
    
    AbstractOcTree* tree = msgToMap(*msg);
    
    tree->getMetricSize(x, y, z);
    r = tree->getResolution();
    ROS_INFO("Size: %f %f %f | Resolution: %f", x,y,z,r);
    
  if(tree){
    
    OcTree* octree = dynamic_cast<OcTree*>(tree);

    OcTreeNode* n = octree->search(0,0,0);
    if (n)
      ROS_INFO("Value:: %f", n->getValue());
    else
      ROS_INFO("Point not found!");

    
//     for(OcTree::leaf_iterator it = octree->begin_leafs(), end = octree->end_leafs(); it != end; ++it)
//     {
//       ROS_INFO("Center: (%f,%f,%f) | Size: %f | Value: %f | Occ: %d", it.getX(), it.getY(), it.getZ(), it.getSize(), it->getValue(), octree->isNodeOccupied(*it));
//       ROS_INFO("Leaf: %d", it.getDepth());
//       cloud.points.push_back(points);
//     }

  }else{
    ROS_ERROR("Octomap conversion error");
    exit(1);
  }
  
}

int main(int argc, char** argv){

  ros::init(argc, argv, "search_octo_point");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/octomap_binary", 1000, octobinCallback);
  
  

  ros::spin();

  return(0);

}

//   // Fill in the cloud data
//   cloud.width    = 5;
//   cloud.height   = 1;
//   cloud.is_dense = false;
//   cloud.points.resize (cloud.width * cloud.height);
// 
//   for (size_t i = 0; i < cloud.points.size (); ++i)
//   {
//     cloud.points[i].x = 1024 * rand () / (RAND_MAX + 1.0f);
//     cloud.points[i].y = 1024 * rand () / (RAND_MAX + 1.0f);
//     cloud.points[i].z = 1024 * rand () / (RAND_MAX + 1.0f);
//   }
// 
//   pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);