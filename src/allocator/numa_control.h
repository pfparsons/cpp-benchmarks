#ifndef MG_NUMA_CONTROL_H
#define MG_NUMA_CONTROL_H

namespace mg {
    /*
     * Experiment:
     * - get available numa nodes
     * - get cache info
     * - Get main memory avail to numa nodes
     * - Get available free in each of above
     * - sort nodes to allocate on by free/available
     *    multi node: - do a probe allocation - and force page faults
     *       - benchmark page migration to other nodes
     */
}

#endif // MG_NUMA_CONTROL_H
