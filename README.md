More information about the History you can refer the document-SCS Introduction(pdf format), you can find it in the above project.

If you have any question and advice, please send me emails: shoutrain.goo@gmail.com && shoutrain_goo@aliyun.com

New Beginning - What's the new ComEgg
==================
Although I had a lot of ideas about ComEgg, I don't know what's the new ComEgg.  My current idea is to refactor ComEgg module by module and make every moudle useful.  Sooner or later the ComEgg composed by these useful modules will be useful.

So step by step, module by module, we will see what's the new ComEgg after 3 years.

History - What's the old ComEgg
==================
1. Dec, 2004, spirited by Gene/Cell, I wanted to make new software architecture which is similar with gene/cell system and totally different with current software thinkings, completed the design at the end of the year.
2. Feb ~ Apr, 2005, completed the first version, 0.1, wich can parse XML scripts and run with private PDU on TCP/UDP and work like a route/switch
3. Sep ~ Oct, 2005, completed the second version, 0.1.1, which can work like JRE, some demo established based on ComEgg, and size-variable PDU was supported.
4. Jun ~ Aug, 2009, completed the third version, 0.2, ported from Windows to Linux, supports so plug-in, and made some demos, like an Blog demo.  This phase the XML script was called RDS(Role define Script), and a new part which is named MagicEgg rised.  So RDS+ComEgg<-->MagicEgg on TCP/UDP works the way of Java+JVM+Tomcat+Servlet<-->IE/Firefox/Chrome on HTTP.

Old ComEgg is ACE 5.7.2 and Xerces C++ 3.0.1 based

Log
==================
2014/11/18
---------
1. reverted back to old ComEgg
2. unified code style by refactor PluginExample
3. port Xerces C++ 3.0.1 to 3.1.1
4. decided to replace ACE with native epoll socket

2014/11/20 ~ 2014/11/21
---------
1. refactor network part and has not completed
2. only keep TCP supports and removed UDP supports, maybe add UDP supports later
3. enhance common supports classes and tools
4. replace the error handle stack with normal log system
5. replace eclipse with clion(from jetbrains) due to xml and scheme supports
6. refine schemes and xml files accordingly


