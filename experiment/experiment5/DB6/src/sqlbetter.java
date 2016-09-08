import java.util.Stack;

public class sqlbetter {
	
	static class Tree    // ������
	{
		String action;    // ָ��
		Tree lchild;
		Tree rchild;
		String content;    // ����
		public Tree(){
			String action = null;
			Tree lchild = null;
			Tree rchlid = null;
			String content = null;
			
		}
	}
	
	static String[][] relations = {    // �漰�Ĺ�ϵ
	{"DNO","ESSN","ADDRESS","SALARY","SUPERSSN","ENAME"},
	{"DNO","DNAME","DNEMBER","MGRSSN","BDATE"}};
	
	public static String Search(String attribute)    // Ѱ���������ڵĹ�ϵ
	{
		for(int i = 0; i < 2; i++)
		{
			for(int k = 0; k < relations[i].length; k++)
			{
				if(relations[i][k].equals(attribute))
				{
					if(i == 0)
					{
						return "EMPLOYEE";
					}
					else
					{
						return "DEPARTMENT";
					}
				}
			}
			
		}
		return "NOTHING";
	}
	
	public static Tree original(String query,Tree t)    // ��ʼ����
	{
		String[] b = query.split(" ");
		Tree cn = t,top = cn;
		
		for(int i = 0; i < b.length; i++)
		{
			if(b[i].equals("SELECT") || b[i].equals("PROJECTION") || b[i].equalsIgnoreCase("AVG"))
			{
				cn.action = b[i];
				
			}
			else if(b[i].equals("[") || b[i].equals("]") || b[i].equals(")"))
			{
				continue;
			}
			else if(b[i].equals("("))
			{
				cn.lchild = new Tree();
				cn = cn.lchild;
			}
			else if(b[i].equals("JOIN"))
			{
				
				cn.action = b[i];
				cn.content = null;
				cn.lchild = new Tree();
				cn.lchild.content = b[i-1];
				cn.rchild = new Tree();
				cn.rchild.content = b[i+1];
				i++;
			}
			else
			{
				if(cn.content == null)
				{
					cn.content = "";
				}
				if(b[i+1].equals("JOIN"))
				{
					continue;
				}
				cn.content = cn.content+b[i];
			}
		}
		return top;
	}
	
	public static void PrintTree(Tree t)    // �ȸ�������ӡ
	{
		Tree cn = t;
		Stack<sqlbetter.Tree> s = new Stack();    // ջ
		while(cn != null || !s.empty())
		{
			while(cn != null)
			{
				if(cn.action != null)
				{
					System.out.print(cn.action+ " ");
				}
				if(cn.content != null)		
				{
					System.out.println(cn.content);
				}
				s.push(cn);
				cn=cn.lchild;
			}
			if(!s.empty())
			{
				cn=s.peek();
				s.pop();
				cn=cn.rchild;
			}
			
		}
	}
	
	public static Tree better(Tree t)    // �Ż�
	{
		Tree top = t, join = t, select = t, projection = t, temp = new Tree();
		int i, j;
		join = Find("JOIN",join);
		select = Find("SELECT",select);
		if(top == select)
		{
			top = top.lchild;
		}
		else
		{
			if(top.lchild == select)
			{
				top.lchild = select.lchild;
			}
			else
			{
				top.lchild.lchild = select.lchild;
			}
		}
		String[] a = select.content.split("&");    // select ����
		for(j = 0; j < a.length; j++)
		{
			String rel = Search(a[j].split("=")[0]);    // ȡ���Զ�Ӧ�Ĺ�ϵ
			if(join.lchild.content.equals(rel))
			{
				temp = join.lchild;
				temp.action = "SELECT";
				temp.content = a[j];
				temp.lchild = new Tree();
				temp.lchild.content = rel;
				join.lchild = temp;
			}
			if(join.rchild.content.equals(rel))
			{
				temp = join.rchild;
				temp.action = "SELECT";
				temp.content = a[j];
				temp.lchild = new Tree();
				temp.lchild.content = rel;
				join.rchild = temp;
			}
		}
		projection = top;
		join = top;
		projection = Find("PROJECTION", projection);
		join = Find("JOIN",join);
		if(projection == null)
		{
			return top;    // �Ż����
		}
		a = projection.content.split(",");    // projection ����
		/*����*/
		if(join.lchild.action != null && join.lchild.action.equals("SELECT"))
		{
			String obj = join.lchild.lchild.content;
			temp = join.lchild.lchild;
			temp.action = "PROJECTION";
			temp.content = relations[0][0];
			for(j = 0; j < a.length; j++)
			{
				if(Search(a[j]) == obj)
				{
					temp.content = temp.content + "," +  a[j];
				}
			}
			String[] b = join.lchild.content.split("&");
			for(i = 0; i < b.length; i++)
			{
				String attr = b[i].split("=")[0];
				temp.content = temp.content + "," + attr;
			}
			temp.lchild = new Tree();
			temp.lchild.content = obj;
			join.lchild.lchild = temp;
		}
		else if(join.lchild.action == null)
		{
			String obj = join.lchild.content;
			temp = join.lchild;
			temp.action = "PROJECTION";
			temp.content = relations[0][0];
			for(j = 0; j < a.length; j++)
			{
				if(Search(a[j]) == obj)
				{
					temp.content = temp.content + "," +  a[j];
				}
			}
			temp.lchild = new Tree();
			temp.lchild.content = obj;
			join.lchild = temp;
		}
		/*����*/
		String obj = join.rchild.lchild.content;
		temp = join.rchild.lchild;
		temp.action = "PROJECTION";
		temp.content = relations[0][0];
		for(j = 0; j < a.length; j++)
		{
			if(Search(a[j]) == obj)
			{
				temp.content = temp.content + "," +  a[j];
			}
		}
		String[] b = join.rchild.content.split("&");
		for(i = 0; i < b.length; i++)
		{
			String attr = b[i].split("=")[0];
			temp.content = temp.content + "," + attr;
		}
		temp.lchild = new Tree();
		temp.lchild.content = obj;
		join.rchild.lchild = temp;
		return top;
	}
	
	public static Tree Find(String act,Tree t)    // Ѱ������
	{	
		Tree t1 = t;
		while(!t1.action.equals(act))
		{
			t1 = t1.lchild;
			if(t1.action == null)    // û�ҵ�
			{
				return null;
			}
		}
		return t1;
	}
	
	public static void main(String[] args)
	{
		String sql1 = "SELECT [ ENAME = 'Mary' & DNAME = 'Research' ] ( EMPLOYEE JOIN DEPARTMENT )";
		String sql2 = "PROJECTION [ BDATE ] ( SELECT [ ENAME = 'John' & DNAME = 'Research' ] ( EMPLOYEE JOIN DEPARTMENT ) )";
		String sql3 = "PROJECTION [ DNAME , SALARY ] ( AVG [ SALARY ] ( SELECT [ DNAME = ��Research�� ] ( EMPLOYEE JOIN DEPARTMENT ) ) )";
		Tree f1 = new Tree();
		Tree f2 = new Tree();
		Tree f3 = new Tree();

		f1 = original(sql1,f1);
		PrintTree(f1);
		System.out.println("");
		System.out.println("better one:");
		f1=better(f1);
		PrintTree(f1);
		System.out.println("------------------------");
		
		f2 = original(sql2,f2);
		PrintTree(f2);
		System.out.println("");
		System.out.println("better one:");
		f2=better(f2);
		PrintTree(f2);
		System.out.println("------------------------");

		f3 = original(sql3,f3);
		PrintTree(f3);
		System.out.println("");
		System.out.println("better one:");
		f3=better(f3);
		PrintTree(f3);
		System.out.println("------------------------");
	}
}
