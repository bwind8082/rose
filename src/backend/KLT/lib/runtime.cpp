
#include "sage3basic.h"

#include "MFB/Sage/class-declaration.hpp"
#include "MFB/Sage/driver.hpp"
#include "MFB/KLT/driver.hpp"

#include "MDCG/Core/model.hpp"
#include "MDCG/Core/model-builder.hpp"

#include "KLT/runtime.hpp"
#include "KLT/descriptor.hpp"
#include "KLT/api.hpp"

namespace KLT {

Runtime::Runtime(MFB::Driver<MFB::KLT::KLT> & driver_, MDCG::ModelBuilder & model_builder_) :
  driver(driver_), model_builder(model_builder_),
  tilek_model(model_builder.create()),
  kernel_file_id(0), static_file_id(0),
  host_api(NULL), kernel_api(NULL), call_interface(NULL)
{}

void Runtime::loadModel(const std::string & klt_inc_dir, const std::string & usr_inc_dir) {
  model_builder.add(tilek_model, "data",    klt_inc_dir + "/KLT/RTL", "h");
  model_builder.add(tilek_model, "tile",    klt_inc_dir + "/KLT/RTL", "h");
  model_builder.add(tilek_model, "loop",    klt_inc_dir + "/KLT/RTL", "h");
  model_builder.add(tilek_model, "context", klt_inc_dir + "/KLT/RTL", "h");

  loadExtraModel(usr_inc_dir);

  assert(host_api != NULL);
  host_api->load(model_builder.get(tilek_model));

  assert(kernel_api != NULL);
  kernel_api->load(model_builder.get(tilek_model));
}

MFB::Driver<MFB::KLT::KLT> & Runtime::getDriver() { return driver; }
const MFB::Driver<MFB::KLT::KLT> & Runtime::getDriver() const { return driver; }
MDCG::ModelBuilder & Runtime::getModelBuilder() { return model_builder; }
const MDCG::ModelBuilder & Runtime::getModelBuilder() const { return model_builder; }
API::host_t & Runtime::getHostAPI() { return *host_api; }
const API::host_t & Runtime::getHostAPI() const { return *host_api; }
API::kernel_t & Runtime::getKernelAPI() { return *kernel_api; }
const API::kernel_t & Runtime::getKernelAPI() const { return *kernel_api; }
API::call_interface_t & Runtime::getCallInterface() { return *call_interface; }
const API::call_interface_t & Runtime::getCallInterface() const { return *call_interface; }
MFB::file_id_t Runtime::getKernelFileID() const { return kernel_file_id; }
MFB::file_id_t Runtime::getStaticFileID() const { return static_file_id; }

} // namespace KLT

