# EOrm library

  Realization of ORM technology with Qt.


### License

  Under New BSD License.


### Build

  You can build this library as dynamic or static using you favorite IDE.
  Or directly in terminal (i.e. bash):

    $ cd src/
    $ qmake
    $ make


### Use

  Compile doxygen documentation to total library description.


### Documentation

  Project documentation placed in code and written with doxygen style.
  Doxygen configuration file called "Doxyfile" and placed in root.
  To compile all documentation by default i.e. use terminal:

    $ doxygen

  Now all files placed in folder docs/html/ in HTML format.


### Example

  There is one example in source code, which describe how to create,
  delete, find with EOrm and past find results in Qt`s MVC.
  If you are linux and library not found, try

	$ export LD_LIBRARY_PATH=/path/to/eorm/library:$LD_LIBRARY_PATH


### Changelog

  * v.0.9.0
    - init commit

  * v.0.9.1
    - fix: documentation
    - fix: error reportning

  * v.0.9.2
    - fix: README, LICENSE, documentation
	- add: primary key name setted as in database by default ("id" was before)

