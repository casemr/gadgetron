#pragma once

#include "Gadget.h"
#include "hoNDArray.h"
#include "gadgetron_mricore_export.h"

#include <ismrmrd.h>
#include <complex>

namespace Gadgetron{

    class EXPORTGADGETSMRICORE RemoveROOversamplingGadget :
        public Gadget2<ISMRMRD::AcquisitionHeader,hoNDArray< std::complex<float> > >
    {
    public:
        GADGET_DECLARE(RemoveROOversamplingGadget);

        RemoveROOversamplingGadget();
        virtual ~RemoveROOversamplingGadget();

    protected:

        virtual int process_config(ACE_Message_Block* mb);

        virtual int process(GadgetContainerMessage<ISMRMRD::AcquisitionHeader>* m1,
            GadgetContainerMessage< hoNDArray< std::complex<float> > >* m2);

        // if true, the noise variance is kept unchanged in this process
        bool constant_noise_variance_;
    };
}
