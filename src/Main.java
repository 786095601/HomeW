import java.util.*;


public class Main {
    static String[][]world; //缓存区的游戏地图
public static void main(String[] args) throws InterruptedException {
	System.out.println("ArmyAutomatica Loaded, Ready to Launch!");
	//国际惯例欢迎标语
	Work map1 = new Work();//抽象带师展开棋盘
	world= map1.gen();            //棋盘粗线了！
	map1.print(world);          //棋盘被打印出来了！
	System.out.println("Map generated, release the Characters! Press Enter");
	Work.spawn();
	map1.print(world);          //kono game, hajimaru！
	//<<<<<<<警方突击中<<<<<<<<<
	while (true){
		Work.run();
		map1.print(world);
		Thread.sleep(1000);
	}
	//<<<<<<<<<<<<<<<<<<<<<<<<<<
}
}
class Work //开创工作序列
{
	static int X=10;
	static int Y=10;
	//这个棋盘大小的接口以后再改，目前先这样放着吧
	public String[][] gen() //初始化棋盘生成方法
	{
      String [][]a=new String[X+1][Y+1];                    //开X+1,Y+1个位置把一行一列空出来方便调整
      for(int i=1;i<=X;i++) 
      {
    	  for(int j=1;j<=Y;j++)
    	  {
    		  a[i][j]="口 ";
    	  }
      }
     return a; //把这个初始化的棋盘拿出来
	}
	public void print(String[][] map) //初始化打印方法
	{
		for(int i=1;i<=X;i++) 
	    {
	  	  for(int j=1;j<=Y;j++)
	  	  {
	  		System.out.print(map[i][j]);
	  	  }
	  	    System.out.println();
	}
	}
	
	public static String life(int life,String name) {//控制血条的打印
		String slife="Life("+name+")[";
		for(int i=0;i<life;i++) {
			slife += "=";
		}
		for(int j=10-life;j>0;j--) {
			slife += " ";
		}
		slife += "]";
		return slife;
	}
	
	public static void spawn()//控制初始所有单位的生成
	{
		Horse.spawn();
	}
	public static void run()//每一轮游戏进行所执行的动作
	{
		Horse.AI();
		hamham.create();
	}
}
//邪恶势力登场
class Horse
{
	public static boolean alive = false; //该角色是否在场
	public static int life = 10; //拿这玩意当他生命值
	public static String name = "Horse"; //需要解释？
	
	public static int x=(int)(Math.random()*10+1), y=(int)(Math.random()*10+1);
	
	public static void spawn()
	{
		Main.world[x][y] ="马 ";
		alive = true; //我活辣！
	}
	
	public static void AI() //一个单位要做的事情
	{
		Main.world[x][y] ="口 ";//把自身所在的格子归零
		
		if (x>1&&x<10) {
		x+=(int)((Math.random()+1)*(Math.random()<=0.5?1:-1));
		}
		else if(x<=1) {x++;}
		else {x--;}
		
		if (y>1&&y<10) {
			y+=(int)((Math.random()+1)*(Math.random()<=0.5?1:-1));
			}
			else if(y<=1) {y++;}
			else {y--;}
		
		Main.world[x][y] ="马 ";//把目标格子变成自己
		if (life>0) {life--;}//讲道理，生物赶路后都是会饿的嘛。
		else {
			alive=false;
			System.out.println("您的马死了");
		}
		if (alive==true) {
		System.out.println(Work.life(life, name));
		}
	}	
}

class hamham { //突然想把hamburger叫成hamham我也不知道为什么，反正就是个能吃掉然后补充life的
	public static int x=(int)(Math.random()*10+1), y=(int)(Math.random()*10+1);
	public static boolean alive = true;
	public static void create() {
		Main.world[x][y]="憨";
	}
	public static void eat(){
		if(Horse.x==x&&Horse.y==y) {
			Horse.life++;
			alive=false;
			System.out.println("您马吃撑了");
		}
	}
}