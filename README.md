# TCL (Transparent Checkpoint Library) 
TCL (Transparent Checkpoint Library) is a tool that provide a generic interface for several different Checkpoint/Restart state of the art libraries. It has been developed by the [*Programming Models group*](https://pm.bsc.es/) at the [**Barcelona Supercomputing Center**](http://www.bsc.es/).

It is mainly used, along with Mercurium compiler, to support pragma checkpointing.

Nowadays, TCL implements three different backends: [*FTI (Fault Tolerant Interface)*](https://github.com/leobago/fti), [*SCR (Scalable Checkpoint Restart)*](https://computation.llnl.gov/projects/scalable-checkpoint-restart-for-mpi) and [*VeloC (Very-Low Overhead Checkpointing System)*](https://veloc.readthedocs.io/en/latest/). However, given its simplicity, is quite easy to add new backends.

## Installation
1. TCL needs *MPI* and at least one of the backends (*FTI/SCR/VeloC*) to be built. 
2. Download TCL's code
    1. From our repo
        * Clone TCL's repository

            - From GitHub:

                    $ git clone https://github.com/bsc-pm/TCL.git
        * Run `autoreconf` in the newly created `TCL` directory

                $ cd TCL 
                $ autoreconf -fiv
                <<<autoreconf output>>>
3. Run `configure`. Check the configure flags with 
        $ ./configure --help
    to enable more or less backends in the library. Remember that at least 
    one backend is necessary, as well as MPI. Set the environment variable 
    `TCL-INSTALL` to the directory where you want to install TCL

        $ export TCL-INSTALL=/path/to/install/TCL
        $ ./configure --prefix=$TCL-INSTALL --with-mpi=/path/to/install/MPI --with-(fti/scr/veloc)=/path/to/install/(fti/scr/veloc)
4. Build and install

        $ make
        <<<compilation output>>>
        $ make install

And that's all!

## Contact Information

For questions, suggestions and bug reports, you can contact us through the pm-tools@bsc.es

