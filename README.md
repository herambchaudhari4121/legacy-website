# website
µWebSockets simple chat website written in C++ and vanillaJS™
<HEAD>
<TITLE>A garbage collector for C and C++</title>
</head>
<BODY>
<TABLE cellpadding="10%" bgcolor="#F0F0FF">
  <TR>
  <TD><A HREF="gcinterface.html">Interface Overview</a></td>
  <TD><A HREF="04tutorial.pdf">Tutorial Slides</a></td>
  <TD><A HREF="faq.html">FAQ</a></td>
  <TD><A HREF="simple_example.html">Example</a></td>
  <TD><A HREF="gc_source">Download</a></td>
  <TD><A HREF="license.txt">License</a></td>
  </tr>
</table>
<H1>A garbage collector for C and C++</h1>
<UL>
<LI><A HREF="#where">Where to get the collector</a>
<LI><A HREF="#platforms">Platforms</a>
<LI><A HREF="#multiprocessors">Scalable multiprocessor versions</a>
<LI><A HREF="#details">Some collector details</a>
<LI><A HREF="#further">Further reading</a>
<LI><A HREF="#users">Current users</a>
<LI><A HREF="#collector">Local links for this collector</a>
<LI><A HREF="#background">Local background Links</a>
<LI><A HREF="#contacts">Contacts, Updates, and Reporting Issues<a>
<LI><A HREF="#translations">Translations of this page</a>
</ul>
[ This is an updated version of the page formerly at
<TT>http://www.hpl.hp.com/personal/Hans_Boehm/gc</tt>,
and before that at
<TT>http://reality.sgi.com/boehm/gc.html</tt>
and before that at
<TT>ftp://parcftp.xerox.com/pub/gc/gc.html</tt>. ]
<P>
The <A HREF="http://www.hboehm.info">Boehm</a>-<A HREF="http://www.cs.cornell.edu/annual_report/00-01/bios.htm#demers">Demers</a>-<A HREF="http://www-sul.stanford.edu/weiser/">Weiser</a>
conservative garbage collector can
be used as a garbage collecting
replacement for C <TT>malloc</tt> or C++ <TT>new</tt>.
It allows you to allocate memory basically as you normally would,
without explicitly deallocating memory that is no longer useful.
The collector automatically recycles memory when it determines
that it can no longer be otherwise accessed.
A simple example of such a use is given
<A HREF="simple_example.html">here</a>.
<P>
The collector is also used by a number of programming language
implementations that either use C as intermediate code, want
to facilitate easier interoperation with C libraries, or
just prefer the simple collector interface.
For a more detailed description of the interface, see
<A HREF="gcinterface.html">here</a>.
<P>
Alternatively, the garbage collector  may be used as
a <A HREF="leak.html">leak detector</a>
for C or C++ programs, though that is not its primary goal.
<P>
The arguments for and against conservative garbage collection
in C and C++ are briefly
discussed in
<A HREF="issues.html">issues.html</a>.  The beginnings of
a frequently-asked-questions list are <A HREF="faq.html">here</a>.
<P>
Empirically, this collector works with most unmodified C programs,
simply by replacing
<TT>malloc</tt> with <TT>GC_malloc</tt> calls,
replacing <TT>realloc</tt> with <TT>GC_realloc</tt> calls, and removing
free calls.  Exceptions are discussed
in <A HREF="issues.html">issues.html</a>. 
<H2><A NAME="where">Where to get the collector</a></h2>
<P>
Many versions are available in the
<A HREF="gc_source">
<TT>gc_source</tt></a> subdirectory.
Currently a fairly recent stable version is
<A HREF="gc_source/gc-8.0.4.tar.gz"><TT>gc-8.0.4.tar.gz</tt></a>.
Note that this uses the new version numbering scheme
and may require a separate <TT>libatomic_ops</tt> download (see below).
<P>
If that fails, try the latest explicitly numbered version
in <A HREF="gc_source">
<TT>gc_source</tt></a>.
Later versions may contain additional features, platform support,
or bug fixes, but are likely to be less well tested.
<P>
Version 7.3 and later require that you download a corresponding
version of libatomic_ops, which should be available
in <A HREF="https://github.com/ivmai/libatomic_ops/wiki/Download">
<TT>https://github.com/ivmai/libatomic_ops/wiki/Download</tt></a>.
The current version is also available as
<A HREF="gc_source/libatomic_ops-7.6.10.tar.gz">
<TT>gc_source/libatomic_ops-7.6.10.tar.gz</tt></a>.
You will need to place that in a libatomic_ops
subdirectory.
<P>
Previously it was best to use corresponding versions of gc
and libatomic_ops, but for recent versions, it should be OK to
mix and match them.
<P>
Starting with 8.0, libatomic_ops is only required if the compiler does
not understand C atomics.
<P>
The development version of the GC source code now resides on github,
along with the downloadable packages.
The GC tree itself is at
<A HREF="https://github.com/ivmai/bdwgc/"><TT>https://github.com/ivmai/bdwgc/</tt></a>.
The <TT>libatomic_ops</tt> tree required by the GC is at
<A HREF="https://github.com/ivmai/libatomic_ops/"><TT>https://github.com/ivmai/libatomic_ops/</tt></a>.
<P>
To build a working version of the collector, you will need to do
something like the following, where <TT>D</tt> is the absolute
path to an installation directory:
<PRE>
cd D
git clone git://github.com/ivmai/libatomic_ops.git
git clone git://github.com/ivmai/bdwgc.git
ln -s  D/libatomic_ops D/bdwgc/libatomic_ops
cd bdwgc
autoreconf -vif
automake --add-missing
./configure
make
</pre>
This will require that you have C and C++ toolchains, <TT>git</tt>,
<TT>automake</tt>, <TT>autoconf</tt>, and <TT>libtool</tt> already
installed.
<P>
Historical versions of the source can still be found
on the SourceForge site (project "bdwgc")
<A HREF="http://bdwgc.cvs.sourceforge.net/bdwgc/">here</a>.
<P>
The garbage collector code is copyrighted by
<A HREF="http://hboehm.info">Hans-J. Boehm</a>,
Alan J. Demers,
<A HREF="http://www.xerox.com">Xerox Corporation</a>,
<A HREF="http://www.sgi.com">Silicon Graphics</a>,
and
<A HREF="http://www.hp.com">Hewlett-Packard Company</a>.
It may be used and copied without payment of a fee under minimal restrictions.
See the README file in the distribution or the
<A HREF="license.txt">license</a> for more details.
<B>IT IS PROVIDED AS IS,
WITH ABSOLUTELY NO WARRANTY EXPRESSED OR IMPLIED.  ANY USE IS AT YOUR OWN RISK</b>.
<H2><A NAME="platforms">Platforms</a></h2>
The collector is not completely portable, but the distribution
includes ports to most standard PC and UNIX/Linux platforms.
The collector should work on Linux, *BSD, recent Windows versions,
MacOS X, HP/UX, Solaris,
Tru64, Irix and a few other operating systems.
Some ports are more polished than others.
There are <A HREF="porting.html">instructions</a> for porting the collector
to a new platform.
<P>
Irix pthreads, Linux threads, Win32 threads, Solaris threads
(old style and pthreads),
HP/UX 11 pthreads, Tru64 pthreads, and MacOS X threads are supported
in recent versions.
<H3>Separately distributed ports</h3>
For MacOS 9/Classic use, Patrick Beard's latest port were once available from
<TT>http://homepage.mac.com/pcbeard/gc/</tt>.
<P>
Several Linux and BSD versions provide prepacked versions of the collector.
The Debian port can be found at
<A HREF="https://packages.debian.org/sid/libgc-dev">
https://packages.debian.org/sid/libgc-dev</a>.
<H2><A NAME="multiprocessors">Scalable multiprocessor versions</a></h2>
Kenjiro Taura, Toshio Endo, and Akinori Yonezawa developed a parallel collector
based on this one.  It was once available from <TT>http://www.yl.is.s.u-tokyo.ac.jp/gc/</tt>
Their collector takes advantage of multiple processors
during a collection.  Starting with collector version 6.0alpha1
we also do this, though with more modest processor scalability goals.
Our approach is discussed briefly in
<A HREF="scale.html"><TT>scale.html</tt></a>.
<H2><A NAME="details">Some Collector Details</a></h2>
The collector uses a <A HREF="complexity.html">mark-sweep</a> algorithm.
It provides incremental and generational
collection under operating systems which provide the right kind of
virtual memory support.  (Currently this includes SunOS[45], IRIX,
OSF/1, Linux, and Windows, with varying restrictions.)
It allows <A HREF="finalization.html"><I>finalization</i></a> code
to be invoked when an object is collected.
It can take advantage of type information to locate pointers if such
information is provided, but it is usually used without such information.
ee the README and
<TT>gc.h</tt> files in the distribution for more details.
<P>
For an overview of the implementation, see <A HREF="gcdescr.html">here</a>.
<P>
The garbage collector distribution includes a C string
(<A HREF="gc_source/cordh.txt"><I>cord</i></a>) package that provides
for fast concatenation and substring operations on long strings.
A simple curses- and win32-based editor that represents the entire file
as a cord is included as a
sample application.
<P>
Performance of the nonincremental collector is typically competitive
with malloc/free implementations.  Both space and time overhead are
likely to be only slightly higher
for programs written for malloc/free
(see Detlefs, Dosser and Zorn's
<A HREF="ftp://ftp.cs.colorado.edu/pub/techreports/zorn/CU-CS-665-93.ps.Z">Memory Allocation Costs in Large C and C++ Programs</a>.)
For programs allocating primarily very small objects, the collector
may be faster; for programs allocating primarily large objects it will
be slower.  If the collector is used in a multithreaded environment
and configured for thread-local allocation, it may in some cases
significantly outperform malloc/free allocation in time.
<P>
We also expect that in many cases any additional overhead
will be more than compensated for by decreased copying etc.
if programs are written
and tuned for garbage collection.
<H1><A NAME="further">Further Reading:</a></h1>
<B>The beginnings of a frequently asked questions list for this
collector are <A HREF="faq.html">here</a></b>.
<P>
<B>The following provide information on garbage collection in general</b>:
<P>
Paul Wilson's <A HREF="ftp://ftp.cs.utexas.edu/pub/garbage">garbage collection ftp archive</a> and <A HREF="ftp://ftp.cs.utexas.edu/pub/garbage/gcsurvey.ps">GC survey</a>.
<P>
The Ravenbrook <A HREF="http://www.memorymanagement.org/">
Memory Management Reference</a>.
<P>
David Chase's
<A HREF="http://www.iecc.com/gclist/GC-faq.html">GC FAQ</a>.
<P>
Richard Jones'
<A HREF="http://www.ukc.ac.uk/computer_science/Html/Jones/gc.html">
GC page</a> and
<A HREF="//www.cs.kent.ac.uk/people/staff/rej/gcbook/gcbook.html">
his book</a>.
<P>
<B>The following papers describe the collector algorithms we use
and the underlying design decisions at
a higher level.</b>
<P>
(Some of the lower level details can be found
<A HREF="gcdescr.html">here</a>.)
<P>
The first one is not available
electronically due to copyright considerations.  Most of the others are
subject to ACM copyright.
<P>
Boehm, H., &quot;Dynamic Memory Allocation and Garbage Collection&quot;, <I>Computers in Physics
9</i>, 3, May/June 1995, pp. 297-303.  This is directed at an otherwise sophisticated
audience unfamiliar with memory allocation issues.  The algorithmic details differ
from those in the implementation.  There is a related letter to the editor and a minor
correction in the next issue.
<P>
Boehm, H., and <A HREF="http://www.ubiq.com/hypertext/weiser/weiser.html">M. Weiser</a>,
<A HREF="../spe_gc_paper">&quot;Garbage Collection in an Uncooperative Environment&quot;</a>,
<I>Software Practice &amp; Experience</i>, September 1988, pp. 807-820.
<P>
Boehm, H., A. Demers, and S. Shenker, <A HREF="papers/pldi91.ps.Z">&quot;Mostly Parallel Garbage Collection&quot;</a>, Proceedings
of the ACM SIGPLAN '91 Conference on Programming Language Design and Implementation,
<I>SIGPLAN Notices 26</i>, 6 (June 1991), pp. 157-164.
<P>
Boehm, H., <A HREF="papers/pldi93.ps.Z">&quot;Space Efficient Conservative Garbage Collection&quot;</a>, Proceedings of the ACM
SIGPLAN '93 Conference on Programming Language Design and Implementation, <I>SIGPLAN
Notices 28</i>, 6 (June 1993), pp. 197-206.
<P>
Boehm, H., &quot;Reducing Garbage Collector Cache Misses&quot;,
<i> Proceedings of the 2000 International Symposium on Memory Management </i>.
<a HREF="http://portal.acm.org/citation.cfm?doid=362422.362438">
Official version.</a>
<a HREF="http://www.hpl.hp.com/techreports/2000/HPL-2000-99.html">
Technical report version.</a>  Describes the prefetch strategy
incorporated into the collector for some platforms.  Explains why
the sweep phase of a "mark-sweep" collector should not really be
a distinct phase.
<P>
M. Serrano, H. Boehm,
&quot;Understanding Memory Allocation of Scheme Programs&quot;,
<i>Proceedings of the Fifth ACM SIGPLAN International Conference on
Functional Programming</i>, 2000, Montreal, Canada, pp. 245-256.
<a HREF="http://www.acm.org/pubs/citations/proceedings/fp/351240/p245-serrano/">
Official version.</a>
<a HREF="http://www.hpl.hp.com/techreports/2000/HPL-2000-62.html">
Earlier Technical Report version.</a>  Includes some discussion of the
collector debugging facilities for identifying causes of memory retention.
<P>
Boehm, H.,
&quot;Fast Multiprocessor Memory Allocation and Garbage Collection&quot;,
<a HREF="http://www.hpl.hp.com/techreports/2000/HPL-2000-165.html">
HP Labs Technical Report HPL 2000-165</a>.  Discusses the parallel
collection algorithms, and presents some performance results.
<P>
Boehm, H., &quot;Bounding Space Usage of Conservative Garbage Collectors&quot;,
<i>Proceeedings of the 2002 ACM SIGPLAN-SIGACT Symposium on Principles of
Programming Languages</i>, Jan. 2002, pp. 93-100.
<a HREF="http://portal.acm.org/citation.cfm?doid=503272.503282">
Official version.</a>
<a HREF="http://www.hpl.hp.com/techreports/2001/HPL-2001-251.html">
Technical report version.</a>
Includes a discussion of a collector facility to much more reliably test for
the potential of unbounded heap growth.
<P>
<B>The following papers discuss language and compiler restrictions necessary to guaranteed
safety of conservative garbage collection.</b>
<P>
We thank John Levine and JCLT for allowing
us to make the second paper available electronically, and providing PostScript for the final
version.
<P>
Boehm, H., <A HREF="papers/pldi96.ps.gz">``Simple
Garbage-Collector-Safety''</a>, Proceedings
of the ACM SIGPLAN '96 Conference on Programming Language Design
and Implementation.
<P>
Boehm, H., and D. Chase,  <A HREF="papers/boecha.ps.gz">
``A Proposal for Garbage-Collector-Safe C Compilation''</a>,
<I>Journal of C  Language Translation 4</i>, 2 (Decemeber 1992), pp. 126-141.
<P>
<B>Other related information: </b>
<P>
The Detlefs, Dosser and Zorn's <A HREF="ftp://ftp.cs.colorado.edu/pub/techreports/zorn/CU-CS-665-93.ps.Z">Memory Allocation Costs in Large C and C++ Programs</a>.
 This is a performance comparison of the Boehm-Demers-Weiser collector to malloc/free,
using programs written for malloc/free.
<P>
Joel Bartlett's <A HREF="ftp://ftp.digital.com/pub/DEC/CCgc">mostly copying conservative garbage collector for C++</a>.
<P>
John Ellis and David Detlef's <A HREF="ftp://parcftp.xerox.com/pub/ellis/gc/gc.ps">Safe Efficient Garbage Collection for C++</a> proposal.
<P>
Henry Baker's <A HREF="http://home.pipeline.com/~hbaker1/">paper collection</a>.
<P>
Slides for Hans Boehm's <A HREF="myths.ps">Allocation and GC Myths</a> talk.
<H1><A NAME="users">Current users:</a></h1>
<P>
<B>This section has not been updated recently.</B>
<P>
Known current users of some variant of this collector include:
<P>
The runtime system for <A HREF="http://gcc.gnu.org/java">GCJ</a>,
the static GNU java compiler.
<P>
<A HREF="http://w3m.sourceforge.net/">W3m</a>, a text-based web browser.
<P>
Some versions of the Xerox DocuPrint printer software.
<P>
The <A HREF="http://www.mozilla.org">Mozilla</a> project, as leak
detector.
<P>
The <A HREF="http://www.go-mono.com">Mono</a> project,
an open source implementation of the .NET development framework.
<P>
The <A HREF="http://www.gnu.org/projects/dotgnu/">DotGNU Portable.NET
project</a>, another open source .NET implementation.
<P>
The <A HREF="http://irssi.org/">Irssi IRC client</a>.
<P>
<A HREF="http://titanium.cs.berkeley.edu/">The Berkeley Titanium project</a>.
<P>
<A HREF="http://www.nag.co.uk/nagware_fortran_compilers.asp">The NAGWare f90 Fortran 90 compiler</a>.
<P>
Elwood Corporation's <A HREF="http://www.elwood.com/eclipse-info/index.htm">
Eclipse</a> Common Lisp system, C library, and translator.
<P>
The <A HREF="http://www-sop.inria.fr/mimosa/fp/Bigloo/">Bigloo
Scheme</a>
and <A HREF="http://kaolin.unice.fr/~serrano/camloo.html">Camloo ML
compilers</a>
written by Manuel Serrano and others.
<P>
Brent Benson's <A HREF="http://ftp.cs.indiana.edu/pub/scheme-repository/imp/">libscheme</a>.
<P>
The <A HREF="http://www.cs.rice.edu/CS/PLT/packages/mzscheme/index.html">MzScheme</a> scheme implementation.
<P>
The <A HREF="http://www.cs.washington.edu/research/projects/cecil/www/cecil-home.html">University of Washington Cecil Implementation</a>.
<P>
<A HREF="http://www.icsi.berkeley.edu:80/Sather/">The Berkeley Sather implementation</a>.
<P>
<A HREF="http://www.cs.berkeley.edu/~harmonia/">The Berkeley Harmonia Project</a>.
<P>
The <A HREF="http://www.cs.arizona.edu/sumatra/toba/">Toba</a> Java Virtual
Machine to C translator.
<P>
The <A HREF="http://www.gwydiondylan.org/">Gwydion Dylan compiler</a>.
<P>
The <A HREF="http://gcc.gnu.org/onlinedocs/gcc/Objective-C.html">
GNU Objective C runtime</a>.
<P>
<A HREF="http://www.math.uiuc.edu/Macaulay2">Macaulay 2</a>, a system to support
research in algebraic geometry and commutative algebra.
<P>
The <A HREF="http://www.vestasys.org/">Vesta</a> configuration management
system.
<P>
<A HREF="http://www.visual-prolog.com/vip6">Visual Prolog 6</a>.
<P>
<A HREF="http://asymptote.sf.net">Asymptote LaTeX-compatible
vector graphics language.</a>

<H1><A NAME="collector">More collector information at this site</a></h1>
<A HREF="simple_example.html">A simple illustration of how to build and
use the collector.</a>.
<P>
<A HREF="gcinterface.html">Description of alternate interfaces to the
garbage collector.</a>
<P>
<A HREF="04tutorial.pdf">Slides from an ISMM 2004  tutorial about the GC.</a>
<P>
<A HREF="faq.html">A FAQ (frequently asked questions) list.</a></td>
<P>
<A HREF="leak.html">How to use the garbage collector as a leak detector.</a>
<P>
<A HREF="debugging.html">Some hints on debugging garbage collected
applications.</a>
<P>
<A HREF="gcdescr.html">An overview of the implementation of the
garbage collector.</a>
<P>
<A HREF="porting.html">Instructions for porting the collector to new
platforms.</a>
<P>
<A HREF="tree.html">The data structure used for fast pointer lookups.</a>
<P>
<A HREF="scale.html">Scalability of the collector to multiprocessors.</a>
<P>
<A HREF="gc_source">Directory containing garbage collector source.</a>

<H1><A NAME="background">More background information at this site</a></h1>
<A HREF="bounds.html">An attempt to establish a bound on space usage of
conservative garbage collectors.</a>
<P>
<A HREF="complexity.html">Mark-sweep versus copying garbage collectors
and their complexity.</a>
<P>
<A HREF="conservative.html">Pros and cons of conservative garbage collectors,
in comparison to other collectors.
</a>
<P>
<A HREF="issues.html">Issues related to garbage collection vs.
manual memory management in C/C++.</a>
<P>
<A HREF="example.html">An example of a case in which garbage collection
results in a much faster implementation as a result of reduced
synchronization.</a>
<P>
<A HREF="nonmoving">Slide set discussing performance of nonmoving
garbage collectors.</a>
<P>
<A HREF="http://hboehm.info/popl03/web">
Slide set discussing <I>Destructors, Finalizers, and Synchronization</i>
(POPL 2003).</a>
<P>
<A HREF="http://portal.acm.org/citation.cfm?doid=604131.604153">
Paper corresponding to above slide set.</a>
(<A HREF="http://www.hpl.hp.com/techreports/2002/HPL-2002-335.html">
Technical Report version</a>.)
<P>
<A HREF="gc_bench.html">A Java/Scheme/C/C++ garbage collection benchmark.</a>
<P>
<A HREF="myths.ps">Slides for talk on memory allocation myths.</a>
<P>
<A HREF="gctalk.ps">Slides for OOPSLA 98 garbage collection talk.</a>
<P>
<A HREF="papers">Related papers.</a>
<H1><A NAME="contacts">Contacts, Updates, and Reporting Issues<a></h1>
<P>
For current updates on the collector and information on reporting issues,
please see the <A HREF="https://github.com/ivmai/bdwgc#feedback-contribution-questions-and-notifications">
bdwgc github page</a>.
<P>
There used to be a pair of mailing lists for GC discussions. Those are no longer active.
Please see the above page for pointers to the archives.
<P>
Some now ancient discussion of the collector took place on the gcc
java mailing list, whose archives appear


 
</body>
</html>
