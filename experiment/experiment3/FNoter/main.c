#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <mysql.h>
#include <string.h>

#define QLEN 1130
#define PAAMOUNT 10
#define PALEN 51
#define CONTLEN 51

/* ���ܱ�
1.�����û�    // Ψһ���ǿ�Լ��
    INSERT INTO user VALUES('%nickname%','%email%','%password%','%reg_time%','%log_time%');
2.����ʼ�    // �û��Զ���Լ��
    INSERT INTO note VALUES('%title%','%username%','%keyword%','%ncontent%','%pub_time%','%mod_time%',%visiable%��%cid%);
3.ɾ������    // ���Լ��
    DELETE FROM category WHERE cname='%cname%';
4.���Ӳ�ѯ:    // %belong.username% �����С����鳤��С������
    SELECT belong.groupname,usergroup.username,usergroup.gdescription FROM belong JOIN usergroup ON belong.groupname=usergroup.gname WHERE belong.username='%belong.username%';
5.Ƕ�ײ�ѯ:    // �� %username% һ������û�
    SELECT username FROM belong WHERE groupname IN (SELECT groupname FROM belong WHERE username='%username%' UNION SELECT gname FROM usergroup WHERE username='%username%') AND username<>'%username%';
6.�����ѯ    // �ʼ�������
    SELECT note.title,COUNT(comment.cid) FROM note LEFT JOIN comment ON note.title = comment.note AND note.username = '%note.username%' GROUP BY note.title;
*/
void printTips();    // ����˵��

int main(int argc, char *argv[])
{
    MYSQL mysql;    // ���ݿ����ӵľ��
    MYSQL_RES *res = NULL;    // ��ѯ��������ṹ����
    MYSQL_ROW row;    // ���һ�в�ѯ������ַ�������
    int i, func, flag = 1;
    char query[QLEN], helpq[QLEN],tmp[PAAMOUNT][PALEN], contmp[CONTLEN];
    char para[PAAMOUNT][PALEN + 2], content[CONTLEN + 2];
    char lastnote[PALEN + 2];
    mysql_init(&mysql);    // ��ʼ��MYSQL�ṹ
    // �������ݿ�
//    if(!mysql_query(&mysql, "CREATE DATABASE noter DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;"))
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create noter successfully!\n");
    if(!mysql_real_connect(&mysql, "127.0.0.1", "root", "sjf0528", "noter", 0, NULL, 0))    // �������ݿ�
	{
		printf("%s\n", mysql_error(&mysql));
		exit(1);
	}
	printf("Access to the noter successfully!\n\n");
	// ������
//    if(mysql_query(&mysql, "CREATE TABLE user(nickname varchar(14) PRIMARY KEY,email varchar(50) UNIQUE,password varchar(20) NOT NULL,reg_time DATETIME NOT NULL,log_time DATETIME) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // �����û���
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(user) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE category(cid INT AUTO_INCREMENT PRIMARY KEY,cname varchar(15) NOT NULL,username varchar(14) NOT NULL,FOREIGN KEY (username) REFERENCES user(nickname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ���������
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(category) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE crelation(outcat INT,incat INT,PRIMARY KEY(outcat,incat),FOREIGN KEY (outcat) REFERENCES category(cid),FOREIGN KEY (incat) REFERENCES category(cid)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ���������ϵ��
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(crelation) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE note(title varchar(20),username varchar(14),keyword varchar(10),ncontent varchar(1000) NOT NULL,pub_time DATETIME NOT NULL,mod_time DATETIME,visiable TINYINT(1) NOT NULL DEFAULT 0 CHECK(visiable IN (1,0)),cid INT,PRIMARY KEY(title,username),FOREIGN KEY (username) REFERENCES user(nickname),FOREIGN KEY (cid) REFERENCES category(cid)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // �����ʼǱ�
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(note) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE note(title varchar(20),username varchar(14),keyword varchar(10),ncontent varchar(1000) NOT NULL,pub_time DATETIME NOT NULL,mod_time DATETIME,cid INT,visible TINYINT(1) NOT NULL DEFAULT 0 CHECK(visiable IN (1,0)),PRIMARY KEY(title,username),FOREIGN KEY (username) REFERENCES user(nickname),FOREIGN KEY (cid) REFERENCES category(cid)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ����С���
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(usergroup) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE belong(username varchar(14),groupname varchar(20),PRIMARY KEY (username,groupname),FOREIGN KEY (username) REFERENCES user(nickname),FOREIGN KEY (groupname) REFERENCES usergroup(gname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ������Ա��
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(belong) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE comment(cid INT AUTO_INCREMENT,note varchar(20) NOT NULL,username varchar(14) NOT NULL,ccontent varchar(300) NOT NULL,ctime DATETIME NOT NULL,PRIMARY KEY (cid),FOREIGN KEY (note) REFERENCES note(title),FOREIGN KEY (username) REFERENCES user(nickname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // �������۱�
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(comment) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE invatation(iid INT AUTO_INCREMENT,icontent varchar(80),itime DATETIME NOT NULL,send varchar(14) NOT NULL,receive varchar(14) NOT NULL,aim varchar(10) NOT NULL,PRIMARY KEY (iid),FOREIGN KEY (send) REFERENCES user(nickname),FOREIGN KEY (receive) REFERENCES user(nickname),FOREIGN KEY (aim) REFERENCES usergroup(gname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // �������뺯��
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(invatation) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE notice(nid INT AUTO_INCREMENT,username varchar(14) NOT NULL,ncontent varchar(40) NOT NULL,ntime DATETIME NOT NULL,PRIMARY KEY (nid),FOREIGN KEY (username) REFERENCES user(nickname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ����ϵͳ�����
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(notice) successfully!\n");
//    if(mysql_query(&mysql, "CREATE TABLE grouplog(gid INT AUTO_INCREMENT,groupname varchar(20) NOT NULL,gcontent varchar(50) NOT NULL,gtime DATETIME NOT NULL,PRIMARY KEY (gid),FOREIGN KEY (groupname) REFERENCES usergroup(gname)) DEFAULT CHARSET=utf8 DEFAULT COLLATE=utf8_general_ci;"))    // ����С����־��
//    {
//        printf("%s\n", mysql_error(&mysql));
//		exit(1);
//    }
//    printf("Create table(grouplog) successfully!\n");
    // ������ͼ����������Ա�鳤���
//    if(mysql_query(&mysql, "CREATE VIEW showgroups AS SELECT usergroup.gname AS groups,usergroup.username AS leader,belong.username AS member FROM usergroup JOIN belong ON usergroup.gname = belong.groupname GROUP BY usergroup.gname,usergroup.username;"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create view showgroups successfully!\n");
    // ������ͼ������֮���ϵ�Լ�����αغͱʼǵĹ�ϵ
//    if(mysql_query(&mysql, "CREATE VIEW showcategorys AS SELECT fc.cname AS father_category,cc.cname AS child_category,title AS notes FROM category AS fc LEFT JOIN crelation ON fc.cid=outcat RIGHT JOIN category AS cc ON incat=cc.cid LEFT JOIN note ON cc.cid=note.cid GROUP BY fc.cid,cc.cid,note.cid;"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create view showgroups successfully!\n");
    // ����������������
//    if(mysql_query(&mysql, "CREATE INDEX category_name ON category(cname);"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create Index on category(cname) successfully!\n");
	// �����������ؼ���
//    if(mysql_query(&mysql, "CREATE INDEX note_keyword ON note(keyword);"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create Index on note(keyword) successfully!\n");
    // �����������������Ա����Ա��������
//    if(mysql_query(&mysql, "CREATE TRIGGER tri_add_mem AFTER INSERT ON belong FOR EACH ROW UPDATE usergroup SET mem_num=mem_num+1 WHERE gname=NEW.groupname;"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create Trigger for adding group member successfully!\n");
    // ������������ɾ����Ա����Ա��������
//    if(mysql_query(&mysql, "CREATE TRIGGER tri_del_mem AFTER DELETE ON belong FOR EACH ROW UPDATE usergroup SET mem_num=mem_num-1 WHERE gname=OLD.groupname;"))
//    {
//		printf("%s\n", mysql_error(&mysql));
//		exit(1);
//	}
//	printf("Create Trigger for deleting group member successfully!\n");
	mysql_query(&mysql, "set names gb2312");    // �����ʽ��֧������
	while(flag)
    {
        printTips();
        printf("\nChoose function:");
        scanf("%d", &func);
        getchar();
        system("cls");
        switch(func)
        {
        case 1:
            printf("����1: �����û�\n\n");
            printf("Input nickname:");
            scanf("%s", tmp[0]);
            getchar();
            printf("Input email:");
            scanf("%s", tmp[1]);
            getchar();
            printf("Input password:");
            scanf("%s", tmp[2]);
            getchar();
            printf("Input register time:");
            scanf("%[^\n]", tmp[3]);
            getchar();
            printf("Input last log time:");
            scanf("%[^\n]", tmp[4]);
            getchar();
            for(i = 0; i < 5; i ++)
            {
                if(strcmp("null", tmp[i]))
                {
                    strcpy(para[i],"\'");
                    strcat(para[i], tmp[i]);
                    strcat(para[i],"\'");
                }
                else
                {
                    strcpy(para[i], tmp[i]);
                }
            }
            strcpy(query, "INSERT INTO user VALUES(");
            for(i = 0; i < 5; i ++)
            {
                strcat(query, para[i]);
                if(i != 4)
                {
                    strcat(query, ",");
                }
                else
                {
                    strcat(query, ");");
                }
            }
    //        printf("query:%s\n", query);
            if(mysql_query(&mysql,query))
            {
                printf("Insert failed: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
                continue;
            }
            printf("Insert success!\n");
            // ����ʾ
            strcpy(query,"SELECT * FROM user WHERE nickname=");
            strcat(query,para[0]);
            strcat(query,";");
            if(mysql_real_query(&mysql, query, strlen(query)))    // ��ѯ
            {
                printf("Fail to query: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
                continue;
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(res == NULL)
            {
                printf("Sorry,system error....\n");
                exit(1);
            }
            printf("Please check:\n");
            if((long int)mysql_num_rows(res))
            {

                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    printf("\n--- >>> \n");
                    printf("| Nickname: %s\n", row[0]);
                    printf("| Email: %s\n", row[1]);
                    printf("| Password: %s\n", row[2]);
                    printf("| Register time: %s\n", row[3]);
                    printf("| Last log time: %s\n", row[4]);
                    printf("<<< --- \n");
                }
            }
            mysql_free_result(res);    // �ͷŽ����
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 2:
            printf("����2: ����ʼ�\n\n");
            printf("Input title:");
            scanf("%[^\n]", tmp[0]);
            getchar();
            printf("Input username:");
            scanf("%s", tmp[1]);
            getchar();
            printf("Input keyword:");
            scanf("%s", tmp[2]);
            getchar();
            printf("Input content:");
            scanf("%[^\n]", contmp);
            getchar();
            printf("Input publish time:");
            scanf("%[^\n]", tmp[4]);
            getchar();
            printf("Input last modify time:");
            scanf("%[^\n]", tmp[5]);
            getchar();
            printf("Visible(1 for yes, 0 for no):");
            scanf("%s", tmp[7]);
            getchar();
            if(strcmp("0",tmp[7]) && strcmp("1",tmp[7]))
            {
                printf("Invalid visible.\n");
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
                continue;
            }
            // չʾ���п�ѡ����
            strcpy(helpq,"SELECT cid,cname FROM category WHERE username=\'");
            strcat(helpq,tmp[1]);
            strcat(helpq,"\';");
            if(mysql_real_query(&mysql, helpq, strlen(helpq)))    // ��ѯ
            {
                exit(1);
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(!(long int)mysql_num_rows(res))
            {
                strcpy(tmp[6], "null");
            }
            else
            {
                printf("Here are all your categories:\n");
                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    printf("%-3s : %s\n", row[0], row[1]);
                }
                printf("\nPlease choose category ID:");
                scanf("%s", tmp[6]);
                getchar();
            }
            mysql_free_result(res);    // �ͷŽ����

            for(i = 0; i < 8; i ++)
            {
                if(i != 3)
                {
                    if(strcmp("null", tmp[i]))
                    {
                        if(i != 6 && i != 7)
                        {
                            strcpy(para[i],"\'");
                            strcat(para[i], tmp[i]);
                            strcat(para[i],"\'");
                        }
                        else
                        {
                            strcpy(para[i], tmp[i]);
                        }
                    }
                    else
                    {
                        strcpy(para[i], tmp[i]);
                    }
                }
                else
                {
                    if(strcmp("null", contmp))
                    {
                        strcpy(content,"\'");
                        strcat(content, contmp);
                        strcat(content,"\'");
                    }
                    else
                    {
                        strcpy(content, "null");
                    }
                }
            }
            strcpy(query, "INSERT INTO note VALUES(");
            for(i = 0; i < 8; i ++)
            {
                if(i != 3)
                {
                    strcat(query, para[i]);
                }
                else
                {
                    strcat(query, content);
                }
                if(i != 7)
                {
                    strcat(query, ",");
                }
                else
                {
                    strcat(query, ");");
                }
            }
//            printf("query:%s\n", query);
            if(mysql_query(&mysql,query))
            {
                printf("Insert failed: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
                continue;
            }
            printf("Insert success!\n");
            // ����ʾ
            strcpy(query,"SELECT * FROM note WHERE title=");
            strcat(query,para[0]);
            strcat(query,"AND username=");
            strcat(query,para[1]);
            strcat(query,";");
            if(mysql_real_query(&mysql, query, strlen(query)))    // ��ѯ
            {
                printf("Fail to query: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
                continue;
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(res == NULL)
            {
                printf("Sorry,system error....\n");
                exit(1);
            }
            printf("Please check:\n");
            if((long int)mysql_num_rows(res))
            {

                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    printf("\n--- >>> \n");
                    printf("| Title: %s\n", row[0]);
                    printf("| User: %s\n", row[1]);
                    printf("| Keyword: %s\n", row[2]);
                    printf("| Content: %s\n", row[3]);
                    printf("| Publish time: %s\n", row[4]);
                    printf("| Last modify time: %s\n", row[5]);
                    printf("| Visible: %s\n", row[6]);
                    printf("| Category ID: %s\n", row[7]);
                    printf("<<< --- \n");
                }
            }
            mysql_free_result(res);    // �ͷŽ����
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 3:
            printf("����3: ɾ������\n\n");
            printf("Input category name:");
            scanf("%s",para[0]);
            getchar();
            strcpy(query, "DELETE FROM category WHERE cname=\'");
            strcat(query, para[0]);
            strcat(query, "\';");
    //        printf("query:%s\n", query);
            if(mysql_query(&mysql,query))
            {
                printf("%s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
            }
            printf("Delete success!\n");
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 4:
            printf("����4����ѯĳ�û������С����Ϣ\n\n");
            printf("Input user's nickname:");
            scanf("%s",para[0]);
            getchar();
            strcpy(query, "SELECT belong.groupname,usergroup.username,usergroup.gdescription FROM belong JOIN usergroup ON belong.groupname=usergroup.gname WHERE belong.username=\'");
            strcat(query, para[0]);
            strcat(query, "\';");
    //        printf("query:%s\n", query);
            if(mysql_real_query(&mysql, query, strlen(query)))    // ��ѯ
            {
                printf("Fail to query: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(res == NULL)
            {
                printf("Sorry,system error...\n");
                exit(1);
            }
            printf("%ld group(s) in total.\n", (long int)mysql_num_rows(res));    // �������
            if((long int)mysql_num_rows(res))
            {

                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    printf("\n--- >>> \n");
                    printf("| Group name: %s\n", row[0]);
                    printf("| Group leader: %s\n", row[1]);
                    printf("| Group description: %s\n", row[2]);
                    printf("<<< --- \n");
                }
            }
            mysql_free_result(res);    // �ͷŽ����
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 5:
            printf("����5: ��ѯ��ĳ�û���ͬһ��С����û�\n\n");
            printf("Input user's nickname:");
            scanf("%s",para[0]);
            getchar();
            strcpy(query, "SELECT groupname,username FROM belong WHERE groupname IN (SELECT groupname FROM belong WHERE username=\'");
            strcat(query, para[0]);
            strcat(query, "\' UNION SELECT gname FROM usergroup WHERE username=\'");
            strcat(query, para[0]);
            strcat(query, "\') AND username<>\'");
            strcat(query, para[0]);
            strcat(query, "\';");
    //        printf("query:%s\n", query);
            if(mysql_real_query(&mysql, query, strlen(query)))    // ��ѯ
            {
                printf("Fail to query: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(res == NULL)
            {
                printf("Sorry, system error...\n");
                exit(1);
            }
            printf("%ld user(s) in total.\n", (long int)mysql_num_rows(res));    // �������
            if((long int)mysql_num_rows(res))
            {
                printf("\n--- >>> \n");
                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    if(strcmp(lastnote,row[0]))
                    {
                        printf("|%10s|\n", row[0]);
                        strcpy(lastnote,row[0]);
                    }
                    printf("\t%s\n", row[1]);
                }
                printf("<<< --- \n");
            }
            mysql_free_result(res);    // �ͷŽ����
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 6:
            printf("����6: ��ѯĳ�û���������ĳ�������۵ıʼ�\n\n");
            printf("Input user's nickname:");
            scanf("%s",para[0]);
            getchar();
            printf("Input minimum comment number:");
            scanf("%s",para[1]);
            getchar();
            strcpy(query, "SELECT note.title, COUNT(comment.cid) FROM note JOIN comment ON note.title = comment.note AND note.username =\'");
            strcat(query, para[0]);
            strcat(query, "\' GROUP BY note.title HAVING COUNT(comment.cid) >=");
            strcat(query, para[1]);
            strcat(query, ";");
//            printf("query:%s\n", query);
            if(mysql_real_query(&mysql, query, strlen(query)))    // ��ѯ
            {
                printf("Fail to query: %s\n", mysql_error(&mysql));
                printf("Press any key to return back ... \n");
                getchar();
                system("cls");
            }
            res = mysql_store_result(&mysql);    // ȡ����ѯ���
            if(res == NULL)
            {
                printf("Sorry,system error...\n");
                exit(1);
            }
            printf("\n");
            if((long int)mysql_num_rows(res))
            {
                while ((row = mysql_fetch_row(res)))    // ���ж�ȡ
                {
                    printf("�� %s ��: %s\n", row[0], row[1]);
                }
            }
            mysql_free_result(res);    // �ͷŽ����
            printf("Press any key to return back ... \n");
            getchar();
            system("cls");
            break;
        case 7:
            flag = 0;
            break;
        default:
            printf("Undefined choice.\n");
        }
    }
    mysql_close(&mysql);    // �ر�Mysql����
    return 0;
}

void printTips()
{
    printf("\t\t\t     **>�ʼǹ���ϵͳ<**\n");
    printf("\t\t++-----------------------------------------++\n");
    printf("\t\t++------------------����-------------------++\n");
    printf("\t\t|    1.�����û�                             |\n");
    printf("\t\t|    2.����ʼ�                             |\n");
    printf("\t\t|    3.ɾ������                             |\n");
    printf("\t\t|    4.��ѯĳ�û������С����Ϣ             |\n");
    printf("\t\t|    5.��ѯ��ĳ�û���ͬһ��С����û�       |\n");
    printf("\t\t|    6.��ѯĳ�û���������ĳ�������۵ıʼ�   |\n");
    printf("\t\t|    7.�˳�                                 |\n");
    printf("\t\t++=========================================++\n");
    return;
}

