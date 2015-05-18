More information about the History you can refer the document-SCS Introduction(pdf format), you can find it in the above project.  The current ComEgg will not meet all suggestions in the document. 

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
4. Jun ~ Aug, 2009, completed the third version, 0.2, ported from Windows to Linux, supports so plug-in, and made some demos, like an Blog demo.  This phase the XML script was called RDS(Role define Script), and a new part which is named MagicEgg rised.  So RDS+ComEgg<-->MagicEgg on TCP/UDP works the way of Java+JVM+Tomcat+Servlet<-->IE/Firefox/Chrome on HTTP. (You can find old ComEgg and old MagicEgg in /old)

Old ComEgg is ACE 5.7.2 and Xerces C++ 3.0.1 based

Thinking Log
==================
2015/03/01
---------
Current Status: These days, I got the spirit, but not details.  How can I represent the idea by code and computer?

今年有机会在业余时间找到实际应用点把这个思想用于软件基础体系的改造：先有鸡还是先有蛋？在有鸡和蛋之前鸡和蛋是同一样东西；好比问先有老师还是先有学生，先有人，老师和学生都是人，逐步人在社会分工上有了老师和学生这两种共生的关系；已经科学确认的是：先有蛋白质还是先有DNA？先有RNA，RNA最后分化为蛋白质和DNA两种功能角色；先有脑细胞还是先有心脏细胞？先有干细胞…

就当作兴趣创造，现在不考虑实用，而是通过软件来初步构建这个思想的灵活模型。每周花一点时间进行更新。

2015/03/30
---------
今天找到那个可以形容维度叠加变化的数学初级表达方式，以后有利于更进一步的挖掘。

fn-1<-xn = fn，这里fn-1是低维度的静形态，xn是跃升的动力，fn是高维度的静形态。

对于素数中的Eratosthenes筛选法，用以上粗率可以表示为：f0<-x1=f1<-x2=f2<-x3=f3...fn-1<xn=fn，f0是2到无穷大的自然数，最后的这个fn就是所有素数集合，也可以称之为维度极限。

2015/04/17
---------
fn-1<-xn = fn

其中fn-1可以表示一种维度的稳定态，xn可以作为变化因子，当稳定态fn-1遇到（或者本身就有，只是特定发展进度下触发）xn变化因子后，可能就会产生fn新的稳定态。

2015/05/17
---------
fn-1<-xn=fn中，以SCS的基本思想来实现，执行和角色的分离。fn-1是执行体当前的稳定状态，xn是下一次角色的变化。

执行体保持稳定，角色作为xn一直在跃升变化中。

Change Log
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

2014/11/28 ~ 2015/03/13
---------
1. use epoll to establish network system which can be changed in running-time
2. establish unified message/signal queue for all thread and realize communication between threads
3. re-establish xml parser system
4. new ComEgg will have a real-time changing system, a long time need to realize it

2015/03/14 ~ NOW
---------
1. I gave up developing ComEgg as an realistic project. ComEgg will be an insteresting project for research. 
2. comEgg will be developing as an gene evolution tools.  Same thinking, different roles and same worker bodies.
3. re-factor the infrastructure of ComEgg, include plugin, network, system.
4. re-define the RDS.
5. add log functions to represent the run-time status and information.
6. delete most of obsoleted classes, new ComEgg don't need them.
7. add old ComEgg and MagicEgg into the repo (/old).

