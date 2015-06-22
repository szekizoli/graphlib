========================================================================
    STATIC LIBRARY : graphlib-core Project Overview
========================================================================

The project graphlib was created from a diploma thesis. The goal of  the project is to provide
the scheduling and execution of executable graphs. An executable graph is such directed acyclic
graph that contains a function in its notes. The execution of a node means the evaluation of the
function in the node. A function can be evaluated if all of its input parameters are ready. The
input parameters of a function are defined by the incoming edges of the node that contains the
function.

An executable graph can be executed in a multi-processor environment. To be able to do so
graphlib will contain scheduling algorithms to provide the scheduling plan for the execution.

namespace graphlib.graph
	This contains the definition of a graph.

namespace graphlib.graph.function
	This contains the available functions. A new function can be added by sub-classing the
	Function class.
	
graphlib-core.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

graphlib-core.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
