今年有机会找到实际应用点把这个思想用于软件基础体系的改造：先有鸡还是先有蛋？在有鸡和蛋之前鸡和蛋是同一样东西；好比问先有老师还是先有学生，先有人，老师和学生都是人，逐步人在社会分工上有了老师和学生这两种共生的关系；已经科学确认的是：先有蛋白质还是先有DNA？先有RNA，RNA最后分化为蛋白质和DNA两种功能角色；先有脑细胞还是先有心脏细胞？先有干细胞…

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

2014/11/20 ~ 2014/11/26
---------
1. refactor everything
2. only keep TCP supports and removed UDP supports, maybe add UDP supports later
3. enhance common supports classes and tools
4. replace the error handle stack with normal log system
5. replace eclipse with clion(from jetbrains) due to xml and scheme supports
6. refine schemes and xml files accordingly
7. use the new code-style

2014/11/28 ~ NOW
---------
1. use epoll to establish network system which can be changed in running-time
2. establish unified message/signal queue for all thread and realize communication between threads
3. re-establish xml parser system
4. new ComEgg will have a real-time changing system, a long time need to realize it
