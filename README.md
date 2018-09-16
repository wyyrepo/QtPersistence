QtPersistence - an ORM framework for Qt
---------------------------------------

QtPersistence is a project to create an ORM library for Qt Users. It’s loosely
based on ideas from both the Active Record and Data Mapper Ruby ORM projects.


Currently (as of 0.1) the only thing supported is object saving and loading.
Eventually, the goal is to add support for the following:

* schema generation
* migration of existing objects
* validations
* relationship mapping
* anything else you would expect an ORM framework to support.


Dependencies
------------

* Qt 4.6
* Google Test Framework 1.4.0
* Google Mock Object Framework 1.4.0


Installation Instructions
-------------------------

1. Checkout the project.
2. Configure the build options with CMake.
3. Run 'make'.
4. Run 'make install'.


Notes on Contributing
---------------------

1. Fork the project on Gitorious.
2. Write some code - be sure to follow the HACKING file.
3. Send a merge request.
4. Get your merge request integrated.
5. Have fun!

Be sure to write test cases and verify that they exercise as much of your code
as possible. The git repository is set up to hit the CDash instance at
mattr.info if you want to run an Experimental build to get an idea of what is
and isn't covered by your tests.

