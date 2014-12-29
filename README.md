最近一些感想(2014年12月29日)
==================
觉得国内某些老软件技术人员挺悲哀的——我毕业的时候看过一本讲COM的技术书籍，是国内一个有点名气的技术人翻译，最近遇到这个年纪不小的技术人，沟通了一下，才有此感觉。
我对他的期望很高，抱着对技术前沿人士的尊重，和他沟通了当前技术的发展以及以后的趋势，他却和我沟通一些动手就明白的琐碎基础知识，对当前很多技术的发展和趋势都不是很明白。沟通完之后，发现基本是鸡同鸭讲，感觉很不舒服。
后来和一个和他有交道的朋友沟通，才知道他30岁之后没有就没怎么写过代码了，也没有什么软件架构的成就，原来如此，是我高看他了。
不知我在沟通时对他说的“程序员没有高手、低手，只有勤动手的程序员和不太动手的伪程序员”，他听了内心是什么滋味。也许是国内浮躁的环境造就他，也许他只是一个有能力翻译别人知识的人。不管如何，他当初翻译的书对我还是有帮助的。

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
