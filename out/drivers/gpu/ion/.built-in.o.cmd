cmd_drivers/gpu/ion/built-in.o :=  /root/Android/utulity/arm-eabi-4.6/bin/arm-eabi-ld -EL    -r -o drivers/gpu/ion/built-in.o drivers/gpu/ion/ion.o drivers/gpu/ion/ion_heap.o drivers/gpu/ion/ion_page_pool.o drivers/gpu/ion/ion_system_heap.o drivers/gpu/ion/ion_carveout_heap.o drivers/gpu/ion/ion_chunk_heap.o drivers/gpu/ion/ion_cma_heap.o drivers/gpu/ion/ion_cma_secure_heap.o drivers/gpu/ion/ion_cp_heap.o drivers/gpu/ion/ion_removed_heap.o drivers/gpu/ion/msm/built-in.o 
