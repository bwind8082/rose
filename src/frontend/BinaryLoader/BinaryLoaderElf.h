#ifndef ROSE_BINARYLOADERELF_H
#define ROSE_BINARYLOADERELF_H

#include "BinaryLoader.h"

class BinaryLoaderElf: public BinaryLoader {
public:
    BinaryLoaderElf() {}

    BinaryLoaderElf(const BinaryLoaderElf &other)
        : BinaryLoader(other)
        {}

    virtual ~BinaryLoaderElf() {}

    /* Override virtual methods from BinaryLoader */
public:
    virtual BinaryLoaderElf *clone() const {
        return new BinaryLoaderElf(*this);
    }
    virtual bool can_load(SgAsmGenericHeader*) const;
    virtual void fixupSections(SgAsmInterpretation *interp);
protected:
    virtual SgAsmGenericSectionPtrList order_sections(const SgAsmGenericSectionPtrList&);
    virtual rose_addr_t align_values(SgAsmGenericSection*, Contribution, rose_addr_t *va, rose_addr_t *mem_size,
                                     rose_addr_t *offset, rose_addr_t *file_size, const MemoryMap *current);
};

#endif /*ROSE_BINARYLOADERELF_H*/
