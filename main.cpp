#include <iostream>
#include<windows.h>
#include<mmsystem.h>
using namespace std;

typedef struct node
{
	string song_name;
	string artist;
	string album;
	string song;
	int since;
	float duration;
	struct node *prev,*next;
}node;

class account
{
	public:
			string user_name;
			string email;
			float ph_no;
			string password;
			void create_account();
			bool valid_email(string email);
			bool valid_ph(float ph_no);
			bool login(string name,string pass);
};

bool account :: valid_email(string email)
{
	const string gmailSuffix = "@gmail.com";
    if (email.length() < gmailSuffix.length())
        return false;
    return email.compare(email.length() - gmailSuffix.length(), gmailSuffix.length(), gmailSuffix) == 0;
    if (valid_email(email))
    {
        cout << "\n\t\t\t\t\t  The email address is valid." << endl;
    }
    else
    {
        cout << "\n\t\t\t\t\t  The email address is not valid." << endl;
    }
}

bool account :: valid_ph(float ph_no)
{

    return (ph_no > 999999999 && ph_no < 10000000000);
}

void account :: create_account()
{
	cout<<"\n\t\t\t\tENTER THE USER NAME    : ";
	getline(cin,user_name);
	cout<<"\n\t\t\t\tENTER THE E-MAIL       : ";
	getline(cin,email);
	while (!valid_email(email)) {
        cout << "\n\t\t\tINVALID E-MAIL ADDRESS! PLEASE ENTER A VALID E-MAIL ADDRESS : ";
        getline(cin, email);
    }
    cout<<"\n\t\t\t\tENTER THE PHONE NUMBER : ";
    cin>>ph_no;
    fflush(stdin);
    while (!valid_ph(ph_no)) {
        cout << "\n\t\t\tINVALID PHONE NUMBER! PLEASE ENTER VALID PHONE NUMBER       : ";
        cin >> ph_no;
        fflush(stdin);
    }
    cout<<"\n\t\t\t\tENTER THE PASSWORD     : ";
    cin>>password;
	cin.ignore();
	cout<<"\n\t\t\t\t\t  ACCOUNT CREATED SUCCESSFULLY!"<<endl;
}

bool account :: login(string name,string pass)
{
	if(user_name==name)
	{
		if(password==pass)
			return true;
		else
			cout<<"\n\t\t\t\t\t  PASSWORD DO NOT MATCH !"<<endl;
			return false;

	}
	else
		cout<<"\n\t\t\t\t\t  USER NAME NOT FOUND !"<<endl;
		return false;
}
class Music_player
{
	public:
		Music_player();
		void addsong(string song,string song_name,string artist,string album,int since,float duration);
		void playsong();
		int deletesong(string song_name);
		void nextsong();
		void prevsong();
		void loopsong();
		void displaysongs();
		int searchsong(string song_name);
		node *head;
		node *tail;
		node *currentsong;
};

Music_player :: Music_player()
{
	head=NULL;
	tail=NULL;
	currentsong=NULL;
}

void Music_player :: addsong(string song,string song_name,string album,string artist,int since,float duration)
{
		node *temp=new node;
		temp->song_name=song_name;
		temp->song=song;
		temp->album=album;
		temp->artist=artist;
		temp->since=since;
		temp->duration=duration;
		temp->prev=tail;
		temp->next=NULL;

		if(head==nullptr)
		{
			head=temp;
			currentsong=temp;
		}
		else
		{
			tail->next=temp;
		}
		tail=temp;
}

void Music_player :: playsong()
{
	if(currentsong!=NULL)
	{
		int choice;
		cout<<"\n\t\t\t\t         NOW PLAYING!"<<currentsong->song_name<<endl;
		cout<<"\t\t\t\t==============================="<<endl;
		cout<<"\t\t\t\tSONG NAME    : "<<currentsong->song_name<<endl;
		cout<<"\t\t\t\tALBUM        : "<<currentsong->album<<endl;
		cout<<"\t\t\t\tARTIST       : "<<currentsong->artist<<endl;
		cout<<"\t\t\t\tSINCE        : "<<currentsong->since<<endl;
		cout<<"\t\t\t\tDURATION     : "<<currentsong->duration<<endl;
		cout<<"\t\t\t\t==============================="<<endl;
        PlaySound(TEXT(currentsong->song.c_str()),NULL,SND_SYNC);
		cout<<"\n\t\t\t\t ENTER 1 TO PLAY SONG IN LOOP! "<<endl;
		cin>>choice;
		if(choice==1)
		{
			loopsong();
		}
		else
			return;

	}
	else
		cout<<"\n\t\t\t\t SORRY!THE SONG "<<currentsong->song_name<<" IS NOT AVAILABLE IN THE PLAYLIST"<<endl;
}

void Music_player :: loopsong()
{
	if(currentsong!=nullptr)
    {

        cout<<"\n\t\t\t\t PLAYING BACK "<<currentsong->song_name<<endl;
        playsong();
    }

}
int Music_player::deletesong(string song_name)
{
        node *ptr = head;
        while(ptr!= nullptr)
		{
            if (ptr->song_name == song_name)
			{
                if (ptr== head && ptr== tail)
				{
                    head = nullptr;
                    tail = nullptr;
                }
				else if (ptr== head)
				{
                    head = ptr->next;
                    head->prev = nullptr;
                }
				else if (ptr== tail)
				{
                    tail = ptr->prev;
                    tail->next = nullptr;
                }
				else
				{
                    ptr->prev->next = ptr->next;
                    ptr->next->prev = ptr->prev;
                }
                delete ptr;
                cout <<"\n\t\t\t\t THE SONG "<< song_name << " HAS BEEN DELETED FROM THE PLAYLIST" << endl;
                return 0;
            }
            ptr = ptr->next;
        }
        cout <<"\n\t\t\t\t THE SONG "<< song_name << " IS NOT IN PLAYLIST FOR DELETION" << endl;
}

void Music_player :: nextsong()
{
	if(currentsong!=NULL && currentsong->next !=NULL )
	{
		cout<<"\n\t\t\t\t	PLAYING NEXT SONG!"<<endl;
		currentsong=currentsong->next;
		playsong();
	}
	else
	{
		cout<<"\n\t\t\t\t CANNOT PLAY THE NEXT SONG SINCE THIS IS THE LAST SONG"<<endl;
	}
}

void Music_player :: prevsong()
{
	if(currentsong!=NULL && currentsong->prev!=NULL )
	{
		cout<<"\n\t\t\t\tPLAYING PREVIOUS SONG!"<<endl;
		currentsong=currentsong->prev;
		playsong();
	}
	else
	{
		cout<<"\n\t\t\t\tCANNOT PLAY THE PREVIOUS SONG SINCE THIS THE FIRST SONG"<<endl;
	}
}

void Music_player :: displaysongs()
{
	if(head==NULL)
		cout<<"\n\t\t\t\tTHE PLAYLIST IS EMPTY"<<endl;
	else
	{
		node *ptr=head;
		while(ptr!=NULL)
		{   cout<<"\n\t\t\t\t\t================================"<<endl;
			cout<<"\t\t\t\t\tSONG NAME    : "<<ptr->song_name<<endl;
			cout<<"\t\t\t\t\tALBUM        : "<<ptr->album<<endl;
			cout<<"\t\t\t\t\tARTIST       : "<<ptr->artist<<endl;
			cout<<"\t\t\t\t\tSINCE        : "<<ptr->since<<endl;
			cout<<"\t\t\t\t\tDURATION     : "<<ptr->duration<<endl;
			cout<<"\t\t\t\t\t================================="<<endl;
			ptr=ptr->next;
		}
	}
}

int Music_player :: searchsong(string song_name)
{
	int choice;
	char play;
	node *ptr=head;
	while(ptr!=nullptr)
	{
		if(ptr->song_name==song_name)
		{
			cout<<"\n\t\t\t\t\t    THE SONG IS AVAILABLE"<<endl;
			cout<<"\t\t\t\t\t================================"<<endl;
			cout<<"\t\t\t\t\tSONG NAME    : "<<ptr->song_name<<endl;
			cout<<"\t\t\t\t\tALBUM        : "<<ptr->album<<endl;
			cout<<"\t\t\t\t\tARTIST       : "<<ptr->artist<<endl;
			cout<<"\t\t\t\t\tSINCE        : "<<ptr->since<<endl;
			cout<<"\t\t\t\t\tDURATION     : "<<ptr->duration<<endl;
			cout<<"\t\t\t\t\t================================"<<endl;
			cout<<"\n\t\t\t\t DO YOU WANT TO PLAY THE SONG(y-YES/n-NO) : ";
			cin>>play;
			if(play=='y')
            {
                PlaySound(TEXT(ptr->song.c_str()),NULL,SND_SYNC);
                cout<<"\n\t\t\t\tENTER 1 TO PLAY THE SONG IN LOOP! : ";
                cin>>choice;
                    if(choice==1)
                    {
                        PlaySound(TEXT(ptr->song.c_str()),NULL,SND_SYNC);
                    }
                    else
                        return 0;
            }
            else
                return 0;
		}
		else
			ptr=ptr->next;

	}
	cout<<"\n\t\t\t\t SORRY! THE SONG "<<song_name<<" IS NOT AVAILABLE IN THE PLAYLIST"<<endl;;
}
int main()
{
	string song,song_name1,song_name2,song_name3,artist,album;
	int since;
	float duration;
	string name,pass;
	cout<<"\n\tWELCOME TO..."<<endl;
	cout<< "\t\t\t''   V       V   IIIII    BBBBB    EEEEE   SSSSS   ''"<<endl;
	cout<< "\t\t\t''    V     V      I      B    B   E       S       ''"<<endl;
	cout<< "\t\t\t''     V   V       I      BBBBB    EEEEE   SSSSS   ''"<<endl;
	cout<< "\t\t\t''      V V        I      B    B   E           S   ''"<<endl;
	cout<< "\t\t\t''       V       IIIII    BBBBB    EEEEE   SSSSS   ''"<<endl;
	Music_player player;
	account a;
	cout<<"\n\n\t\t\t\t\t   ACCOUNT CREATION"<<endl;
	a.create_account();
	system("cls");
	cout<<"\n\n\t\t\t\t\t   LOGIN TO YOUR ACCOUNT"<<endl;
	cout<<"\n\t\t\t\t\tENTER YOUR USER NAME : ";
	getline(cin,name);
	cout<<"\n\t\t\t\t\tENTER YOUR PASSWORD  : ";
	getline(cin,pass);
    if(a.login(name,pass))
    	cout<<"\n\t\t\t\t\t  LOGIN SUCCESSFUL!"<<endl;
    else
    {
		cout<<"\n\t\t\t\t\t  LOGIN UNSUCCESSFUL!"<<endl;
		return 0;
	}

    player.addsong("Malargaley.wav","MALARGALEY","LOVE BIRDS","KS CHITHRA",2000,6.00);
    player.addsong("Malare.wav","MALARE","PREMAM","VIJAY YESUDAS",2015,5.14);
	player.addsong("Vizhi Moodi.wav","VIZHI MOODI","AYAN","HARRIS JEYARAJ",2007,3.23);
	player.addsong("Aga Naga.wav","AGA NAGA","PS 2","ARR",2023,2.53);

	int choice;
	char cont;
	do
	{
	    system("cls");
		cout<<"\n\t\t\t\t\t1.ADD SONG"<<endl;
		cout<<"\t\t\t\t\t2.PLAY SONG"<<endl;
		cout<<"\t\t\t\t\t3.SEARCH SONG"<<endl;
		cout<<"\t\t\t\t\t4.NEXT SONG"<<endl;
		cout<<"\t\t\t\t\t5.PREVIOUS SONG"<<endl;
		cout<<"\t\t\t\t\t6.DISPLAY SONG"<<endl;
		cout<<"\t\t\t\t\t7.DELETE SONG"<<endl;
		cout<<"\n\n\t\t\t\tEnter the choice : ";
		cin>>choice;
		cin.ignore();
		switch(choice)
		{
		case 1:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\tADDING SONG "<<endl;
			cout<<"\n\t\t\t\tEnter the song name   : ";
			getline(cin,song_name1);
			cout<<endl<<"\n\t\t\t\tEnter the song file   : ";
			getline(cin,song);
			cout<<endl<<"\n\t\t\t\tEnter the album       : ";
			getline(cin,album);
			cout<<endl<<"\n\t\t\t\tEnter the artist name : ";
			getline(cin,artist);
			cout<<endl<<"\n\t\t\t\tSince                 : ";
			cin>>since;
			cout<<endl<<"\n\t\t\t\tDuration              : ";
			cin>>duration;
			player.addsong(song,song_name1,album,artist,since,duration);
			cout<<"\n\t\t\t\t  THE SONG "<<song_name1<<" HAS BEEN ADDED TO YOUR PLAYLIST"<<endl;
			break;
		case 2:
		    system("cls");
			player.playsong();
			break;
		case 3:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\t SEARCHING SONG! "<<endl;
			cout<<"\n\t\t\t\t Enter the song name to search : ";
			getline(cin,song_name2);
			player.searchsong(song_name2);
			break;
		case 4:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\t NEXT SONG! "<<endl;
			player.nextsong();
			break;
		case 5:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\t PREVIOUS SONG! "<<endl;
			player.prevsong();
			break;
		case 6:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\t DISPLAYING SONGS! "<<endl;
			player.displaysongs();
			break;
		case 7:
		    system("cls");
		    cout<<"\n\t\t\t\t\t\t DELETING SONG! "<<endl;
			cout<<"\n\t\t\t\t Enter the song name to delete from the playlist : ";
			getline(cin,song_name3);
			player.deletesong(song_name3);
			break;
    	}
    cout<<"\n\t\t\t\t Do you want to continue?(y-yes) : ";
    cin>>cont;
	}while(cont=='y');
    return 0;
}
