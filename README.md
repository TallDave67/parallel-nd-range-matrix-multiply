# Parallel: ND Range Matrix Multiply (DPC++)

Matrix multiplication is easily parallelized and we go a bit beyond basic by implementing an ND Range Kernel with Intel's oneAPI DPC++.

Linux distro "Pop!_OS 21.04"

cmake version 3.18.4

Intel(R) oneAPI DPC++/C++ Compiler 2021.3.0 (2021.3.0.20210619)

## Steps

cd oneapi

./build.sh

./build/nd-range-matrix-multiply

## History

dates: July 13, 2021

duration: 2 hours

### Code from Another Developer

This code came directly from Intel.

[ND Range Matrix Multiply](https://github.com/Apress/data-parallel-CPP/blob/main/samples/Ch04_expressing_parallelism/fig_4_13_nd_range_matrix_multiply.cpp)

Compiler gave warning about loop not being unrolled.  Thomas Kim discusses how this is a false error and the loop is actually unrolled.

[Ignore Warnng about Loop not being Unrolled - @ 23m 24s](https://www.youtube.com/watch?v=_7SNKgw54Yk)

I wanted to see columnar output, so followed Antonio's suggestion.

[Padding a float](https://stackoverflow.com/questions/22509972/how-can-i-pad-a-float-with-leading-zeros-when-using-cout-operator)

Olivier Li showed me how to time code to microsecond accuracy for performance checking.

[Timing with Chrono](https://stackoverflow.com/questions/21856025/getting-an-accurate-execution-time-in-c-micro-seconds)

### Parellel

I placed this in my .bashrc file so the dpcpp compiler can be found.

> export ONEAPI_DIR="/opt/intel/oneapi"

> [ -s "$ONEAPI_DIR/setvars.sh" ] && \. "$ONEAPI_DIR/setvars.sh"  # initialize oneAPI environment

## Output

> 62.8150 61.0702 62.0380 61.6559 64.7695 58.2775 57.9608 64.3574 62.7079 58.1336 66.0439 59.8816 61.3521 59.2256 56.7127 61.9509 
> 
> ...
> 
> 69.8101 64.6917 63.5820 67.9579 64.9832 61.7401 67.3540 66.4323 65.9917 70.3817 66.8222 60.0008 68.0923 65.6087 64.6225 66.2730 
> 
> 65.4712 64.8746 62.0794 65.0475 64.8113 70.0883 66.6456 62.9965 63.6349 62.7693 66.4786 68.0201 63.4512 65.6918 66.8938 65.2959 
> 
> ================================================================
> 
> Elapsed microseconds : 76606
>  
> Elapsed microseconds for check : 176649
> 
> SUCCESS

