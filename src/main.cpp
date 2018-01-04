

#include "common.h"
#include "mapper.h"
#include "measurement_package.h"
#include "ekfslam.h"
#include "draw.h"
#include<iomanip>

using namespace std;

void check_arguments(int argc, char* argv[]) {
  string usage_instructions = "Usage instruction: ";
  usage_instructions += argv[0];
  usage_instructions += " path/to/world.txt path/to/sensor.dat";
  bool has_valid_args = false;

  // make sure the user has provided input and output files
  if (argc == 1) {
    cerr << usage_instructions << endl;
  } else if (argc == 2) {
    cerr << "Please include an output file.\n" << usage_instructions << endl;
  } else if (argc == 3) {
    has_valid_args = true;
  } else if (argc > 3) {
    cerr << "Too many arguments.\n" << usage_instructions << endl;
  }

  if (!has_valid_args) {
    exit(EXIT_FAILURE);
  }
}

int main(int arc, char* argv[])
{
 
   check_arguments(arc, argv);
   
   string in_map_name = argv[1];
   string in_sensor_name = argv[2];
  
   //read the map data for all landmarks
   Mapper mapper;
   mapper.initialize(in_map_name);

   //read the measurements with odometry and radar data
   MeasurementPackage measurements;
   measurements.initialize(in_sensor_name);
   cout << measurements.data.size() << endl;



   Draw draw;

   EKFSLam ekfslam;
   ekfslam.Initialize(mapper.data.size(), 3);
   
   for (int i = 0; i < measurements.data.size(); i++) { 
      const auto& record = measurements.data[i];
      draw.Clear();
      ekfslam.ProcessMeasurement(record);
      draw.Plot_state(ekfslam.mu, ekfslam.Sigma, mapper, ekfslam.observedLandmarks, record.radars);
      draw.Pause();
      stringstream ss;
      ss << setfill('0') << setw(3) << i;
      draw.Save("../images/"+ss.str());
   }
   draw.Show();
 
   return -1;
}
