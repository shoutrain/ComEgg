The project has been suspended a long time since 2005 and 2009, due to goal missing and life maintaining.  Recently I found the goal again, Mobile App, which SCS(ComEgg, MagicEgg and SCS) will serve for.  So the project will soon be launched again.

What's the new ComEgg
==================
1. You can see new ComEgg as a C/C++ version of Java + JVM + Tomcat, you can provide so/dll as servlets.
2. ComEgg works with TCP/UDP instead of HTTP, the protocol data is presented by binary format instead of string format.
3. You can define your own private PDU(Protocol Define Unit, binary) by XML/XSD, size-variable PUD is supported.
4. If you use ComEgg as your backend service provider, you just need to provide so/dll, in which only your service code is involved, you do not pay attention on socket\thread\OS\PDU parser\etc.
5. There are some features like Protocol Buffer.
6. ComEgg will be te backend server for Mobile App, and developer will not think more about distributed system.

Current Status
==================
1. Actually ComEgg has been made since 2005, but the usage is updated now, please see previous section (What's the new ComEgg) to find the new usage.
2. The current primary tasks for the new ComEgg is:
    a. replace ACE with linux epoll.
    b. refactor the XML parser processes.
    c. enhance the .so(linux) supporting.
    d. make it work.
3. Since 2009, ComEgg was ported from Windows to Linux, this time we only support Linux version.  Windows version is considered later.
4. Keep thread-safe for per session.
5. ComEgg doesn't need ACE, but still depends on Log4C and Xerce4C

History
==================
1. Dec, 2004, spirited by Gene/Cell, I wanted to make new software architecture which is similar with gene/cell system and totally different with current software thinkings, completed the design at the end of the year.
2. Feb ~ Apr, 2005, completed the first version, 0.1, which can parse XML scripts and run with private PDU on TCP/UDP and work like a route/switch
3. Sep ~ Oct, 2005, completed the second version, 0.1.1, which can work like JRE, some demo established based on ComEgg, and size-variable PDU was supported.
4. Jun ~ Aug, 2009, completed the third version, 0.2, ported from Windows to Linux, supports so plug-in, and made some demos, like an Blog demo.  This phase the XML script was called RDS(Role Define Script), and a new part which is named MagicEgg rised.  So RDS+ComEgg<-->MagicEgg on TCP/UDP works the way of Java+JVM+Tomcat+Servlet<-->IE/Firefox/Chrome on HTTP.

More information about the History you can refer the document-SCS Introduction(pdf format), you can find it in the above project.

If you have any question and advice, please send me emails: shoutrain.goo@gmail.com && shoutrain_goo@aliyun.com

