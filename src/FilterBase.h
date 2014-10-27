



#ifndef FILTERBASE_H_
#define FILTERBASE_H_

#include "base_types.h"
#include "Properties.h"
#include "VideoFormatDescription.h"
#include "MemoryBuffer.h"

#include <string>
#include <vector>
#include <memory>

using namespace tcam;
// {

enum FILTER_TYPE
{
    FILTER_TYPE_UNKNOWN = 0,
    FILTER_TYPE_CONVERSION,  /* used for static transformations (e.g. colorspace conversions) */
    FILTER_TYPE_INTERPRET,   /* image interpretation / manipulation from device properties */
};


struct FilterDescription
{
    std::string name;
    enum FILTER_TYPE type;

    // 0 == all types
    std::vector<uint32_t> output_fourcc;
    std::vector<uint32_t> input_fourcc;
};


class FilterBase
{
public:

    virtual ~FilterBase () {};

    virtual struct FilterDescription getDescription () const = 0;

    virtual bool transform (MemoryBuffer& in, MemoryBuffer& out ) = 0;

    virtual bool apply (std::shared_ptr<MemoryBuffer>) = 0;

    virtual bool setStatus (PIPELINE_STATUS) = 0;

    virtual PIPELINE_STATUS getStatus () const = 0;

    virtual bool setVideoFormat (const VideoFormat& in, const VideoFormat& out) = 0;
    virtual void getVideoFormat (VideoFormat& in, VideoFormat& out) const = 0;

    virtual void setDeviceProperties (std::vector<std::shared_ptr<Property>>) = 0;

    virtual std::vector<std::shared_ptr<Property>> getFilterProperties () = 0;
};

extern "C"
{
    // the types of the class factories
    typedef FilterBase* create_filter();
    typedef void destroy_filter(FilterBase*);

    /* opaque object that represents the camera */
    struct FB;
    typedef struct FB FB;
    // These two functions serve as entry points to the filter
    // They are used for construction/descruction of your filter
    // The rest can be deduced at runtime

    // FilterBase* create ();

    // void destroy (FilterBase*);

    FB* create ();

    void destroy (FB*);

}

// } /* namespace tcam */

#endif /* FILTERBASE_H_ */
