Galvanic
========

Galvanic is an MIT licensed C++ back-end for creationg JSON-driven APIs.  These APIs can be used in place of:

* LAMP stack
* Nodejs web services

Galvanic is also being developed as an Apache Module (apache-mod-galvanic)


Dependencies
============

* AWS C++ SDK (if you plan to use S3, EFS or other AWS features directly)
* MySQL Connector C++ (if you plan to use MySQL or Aurora DB, or other similar database engines)
* nlohmann's JSON.hpp (included) for parsing JSON
* ZeroTypes (zero.handmade.network)

Alternatives to the Above
=========================

* It is possible to invoke command line utilities for any other cloud service
* It is possible to use JSON on S3 as a database alternative, albeit slightly less performant (20% the speed of MySQL)
* It is possible to make use of Flat Files on an automatically mounted EFS shared module (though it is not atomic)

Core Workflows
==============

1. Take in a JSON request
2. Provide formatted JSON output


How to Extend the Framework
===========================




Using PHP-Galvanic, the PHP Wrapper Script
==========================================

While not preferred, it is possible to handle your incoming request in PHP first, then provide the data to Galvanic by use of the Command Line (described below)


How to Invoke Galvanic From the Command Line
============================================



How to use Galvanic as an Apache Module
=======================================

TBD


Security Thoughts
=================

