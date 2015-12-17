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

2015/05/20
---------
Machine Learning, Linear algebra, Probability theory are necessary, I am learning.

2015/06/10
---------
在学习kNN分类算法时，想到分类这机器算法的实际应用中相当普遍，SCS是否可以应用于分类。

所谓分类，就是一个典型的树状图，有一个根节点，然后向下分出若干的分支，若干的层次。这里的根节点作为第一层，就是f0，第二层就是f1，直到第n层就是fn-1，然后每层的“分”都由xn来实现。这样，fn-1其实很可能是多个点，而xn则是对应多个点的“分”算法。

2015/06/22
---------
在学习机器学习的多项式回归算法中涉及偏微分时，有进入了微积分和多维理论的关系思考，其实真实世界的维度不是有限的，而是无限的，其中应该是有规律的。维度除了由基础维度向高级维度的层层叠加，还有高级维度向基础维度的层层分解，它们的种种关系，本质为一体，之所有多个维度，在于观察者本身所组成的维度和所处的维度。所以SCS在考虑全息进化的时候，应该要考虑这一点。

韩峰老师的TED演讲中，提到两点，一个是比特位的压缩（合并），还有就是“基础协议”。其实我正在做的就是给SCS寻找“基础协议”，这个“基础协议”比面向对象的组件模型要更接近真实宇宙，我相信能给我们带来更好的变化。关于比特位的压缩（合并），其实一直在发生，只不过没有把这个特性独立的抽象出来思考，我得思考一下这个……

2015/07/08
---------
机器学习的课程按照正常的设定，本周已经到了神经网络。

在看到了神经网络为了对多维、多特性的逻辑回归算法进行降维时，这种方法和fn-1<-xn=fn有点类似，而且其神经元部分的拓扑图总发生的计算，和SCS的关联度很高，SCS可以实现这种神经元之间更复杂的计算；反过来神经网络这种方式对SCS在数学和算法上的启示有很多。

2015/08/07
---------
这几天有些很烦人的事情，当然有自己的问题，但更为关键的是，不管工作还是生活，基本的条件是要找到可以沟通的人在一起。

今天的领悟是关于不同xn之间的关系。xn之间应该有一个可以无限二叉树的结构关系。所有的xn都可以从一个总的x继承下来。这样fn要定义基本、统一的功能。整个由xn和fn整合的系统就是一套自循环的系统。

2015/12/17
---------
Found new goal for ComEgg:
1. replace Map/Reduce and Spark as a new distributed framework
2. become a new algorithm for machine learning

Intro and Contact me
==================
More information about the History you can refer the document-SCS Introduction(pdf format), you can find it in the above project.  The current ComEgg will not meet all suggestions in the document. 

If you have any question and advice, please send me emails: shoutrain.goo@gmail.com && shoutrain_goo@aliyun.com

New Beginning - What's the new ComEgg
---------
Although I had a lot of ideas about ComEgg, I don't know what's the new ComEgg.  My current idea is to refactor ComEgg module by module and make every moudle useful.  Sooner or later the ComEgg composed by these useful modules will be useful.

So step by step, module by module, we will see what's the new ComEgg after 3 years.

History - What's the old ComEgg
---------
1. Dec, 2004, spirited by Gene/Cell, I wanted to make new software architecture which is similar with gene/cell system and totally different with current software thinkings, completed the design at the end of the year.
2. Feb ~ Apr, 2005, completed the first version, 0.1, wich can parse XML scripts and run with private PDU on TCP/UDP and work like a route/switch
3. Sep ~ Oct, 2005, completed the second version, 0.1.1, which can work like JRE, some demo established based on ComEgg, and size-variable PDU was supported.
4. Jun ~ Aug, 2009, completed the third version, 0.2, ported from Windows to Linux, supports so plug-in, and made some demos, like an Blog demo.  This phase the XML script was called RDS(Role define Script), and a new part which is named MagicEgg rised.  So RDS+ComEgg<-->MagicEgg on TCP/UDP works the way of Java+JVM+Tomcat+Servlet<-->IE/Firefox/Chrome on HTTP. (You can find old ComEgg and old MagicEgg in /old)

Old ComEgg is ACE 5.7.2 and Xerces C++ 3.0.1 based

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

