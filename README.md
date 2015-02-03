# Fac

Fac is a new build system
(i.e. make/automake/cmake/scons/etc. replacement) that tracks
dependencies automatically.

* Fac automatically tracks build dependencies in a way that is
  independent of programming language.  You are only required to
  specify the minimum of dependencies for each rule, and fac works out
  the rest for you.  If you fail to specify dependencies, fac should
  still build successfully after enough tries, provided your build
  rules fail when dependencies are missing (rather than simply
  producing wrong output).  Once fac has successfully built your
  project, it knows the dependencies of each command, and subsequent
  builds in that source tree will be the same as if you had specified
  all dependencies and all output.

* Fab supports parallel builds.

* You are forced to write your configuration in a language of your own
  choice.  (Or conversely, you are not forced to use a language of
  *my* choice, much less a custom-built language that I developed.)

* Integrates with git, to keep you from forgetting to `git add` a file
  that is needed for the build.

To find out more about fac, including benchmarks and complete
documentation, please visit the fac web page at:

http://physics.oregonstate.edu/~roundyd/fac
