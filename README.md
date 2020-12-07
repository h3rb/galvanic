Galvanic
========

Galvanic is an MIT licensed C++ back-end for creating JSON-driven APIs.  These APIs can be used in place of:

* LAMP stack
* Nodejs web services

Galvanic is also being developed as an Apache Module (apache-mod-galvanic)

### Dependencies

* AWS C++ SDK (if you plan to use S3, EFS or other AWS features directly)
* MySQL Connector C++ (if you plan to use MySQL or Aurora DB, or other similar database engines)
* nlohmann's JSON.hpp (included) for parsing JSON
* ZeroTypes (zero.handmade.network)

See framework/install_dependencies for a complete list.

### Alternatives to the Above

* It is possible to invoke command line utilities for any other cloud service
* It is possible to use JSON on S3 as a database alternative, albeit slightly less performant (20% the speed of MySQL)
* It is possible to make use of Flat Files on an automatically mounted EFS shared module (though it is not atomic)

### Core Workflows

1. Take in a JSON request, including COOKIES, GET and POST variables
2. Process the request and validate the session
3. Provide formatted JSON output to the client

Setting Up
==========

To prime your build environment, make sure to enter the framework/ folder and run ./install_dependencies

Next, set up your stuff by running cmake from the framework/ folder.

After primed, you can now run ./rebuild from within the framework/ folder.

In other words:

```
 $ cd galvanic/framework/
 $ ./install_dependencies
 $ mkdir build
 $ cd build
 $ cmake ..
 $ cd ..
 $ ./rebuild
```

Usage
=====

### How to Invoke Galvanic From the Command Line

The "galvanic" executable ends up in the build/ folder.  This can be placed elsewhere.  See 'Security Thoughts' for tips on where (not) to put it.

The order of command line operations is hard coded in include/commandline.h so it doesn't matter what order you define them when invoking.

Once you have your executable, you'll want to try it out with some test inputs.

#### Command Line Options

* help or -h 

To view this from the command line, invoke "Galvanic -h" or "Galvanic help", which also displays the version information and git's identity SHA-1.

* settings=[/path/to/file.json]
* request=[/path/to/file.json]

### Using PHP-Galvanic, the PHP Wrapper Script

While not preferred, it is possible to handle your incoming request in PHP first, then provide the data to Galvanic by use of the Command Line.  The file php-galvanic/example.php shows how you can use PHP to invoke Galvanic and get a response in JSON.

### Security Thoughts

Place the "galvanic" executable in an offline folder.  It's best not to directly install galvanic to a folder like /usr/bin, so that the placement of galvanic is not globally accessible.  You really only want galvanic running in its own space on your webserver, and nowhere that a web browser would be able to access.


### How to use Galvanic as an Apache 2.4+ Module

The apache-mod-galvanic folder contains a CMakeLists.txt that builds Galvanic as an apache module.  Request data is fed to Galvanic, and Galvanic is expected to produce a response string, usually in JSON, as output.  This string can be empty.  This layer occurs in GalvanicHandler, but is invoked through class Galvanic in Galvanic.h

First, build Galvanic as a command line tool.  Once this happens successfully, use the apache-mod-galvanic configuration to build it as an apache2 module.

To build:

```
 $ cd apache-mod-galvanic/build
 $ cmake ..
 $ make
```

The output will be a file called mod_galvanic.so that can be installed into apache2


How to Extend the Framework
===========================

Note that this document discusses a framework that is a tabula rasa for creating a very fast API.  You will want to customize your galvanic code by adding
additional API endpoints that are custom to your application's needs.

More content will be put here once this part is ready.


Cost and Data
=============

This section contains general design ideas when building a framework using Galvanic.  Depending on your application and budget constraints, this section identifies different approaches to cost with respect to data storage.

It is far cheaper but more latent to use S3 as the primary storage device for ORM.  S3 is about 5 times slower than a request to an Aurora DB (MySQL).  Instead of storing an ORM object in a database, you can store it in S3.  Also, S3 can store binary files easier.  Unlike Aurora, which limits the size of the cluster and its relevent AZ and regions, S3 is high availability globally, which is a benefit, and you can turn on more expensive but less latent features to speed up recall.

Using the S3 data storage model described above, you could also spend money on an EFS data storage system that caches data that is often needed, thereby optimizing speed of recall across multiple framework instances, allowing for not only scalability, but faster recall for users who are active, and after a period of time the data could be transferred from EFS to S3 and therefore S3 is treated like a longer term storage solution.  The latency would only occur when the user has not used the data recently.  There are of course limitations, especially when data across multiple users is being retrieved less often, and also the cost of EFS is significantly hire than S3.  There may be other considerations like multiple-VPCs and multiple-regions.

The conservative method, with limited latency but far higher cost, relies on MySQL databases.  Specifically determining a reliable session requires at least one additional data retrieval during an API request.  Of course you can mix and match the use of MySQL with S3 as you see fit, based on your applications needs.  It's much faster to retrieve session information from MySQL, so it may be enough to reduce latency simply by using MySQL to manage user authentication, while using S3 for all larger datasets.  You may be able to overcome the session lookup by using a feature like IAM, but that is currently beyond the scope of Galvanic (though it could be easily added).

So, with Galvanic, you have this choice to make:
* Rely on S3 as the data storage for JSON objects as well as binary files to build out your API
* Use S3 and EFS
* Use S3 and Aurora or similar MySQL service.


Versioning Philosophy
=====================

Galvanic releases come in major versions only.  Development versions have a .5 added to them.  For example, when Galvanic was initially in development, it received a version number of .5a (`a` meaning alpha), and when it was fully ready for people to derive their own web back ends, this was called version 1.0 -- should Galvanic progress further or require support for later versions of its dependencies, it will be versioned, while in development, as version 1.5a, and in the future a 2.0 release will be made.  No incremental fractional version numbers will ever be used.  This process will continue as long as the Galvanic framework project continues.

Note that the SDKs on which Galvanic depends are updated all the time with incremental releases.  It is possible that when a breaking release of a dependency is made will Galvanic begin to progress toward a new major version.  Galvanic has enough features to be useful, so, with respect to Galvanic itself, a major version is considered a fully tested and ready-to-build version that can be expanded by users.  You do not need to update to a later major version if you are satisfied with the features and have built a derived work, unless a dependency requires it.

If Galvanic's features are expanded, there is a chance that additional dependencies.

### Version History

Galvanic .5a is currently in development.  It will support S3 and MySQL databases, Session management and API requests in JSON.

Galvanic 1.0 will support:
* AWSSDKC++ S3 component only
* MySQLConnector
* JSON
