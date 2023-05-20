#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class pro
{
public:
  string proc_name;
  int pid;
  int arrive;
  int service;
  int service_temp;
  int turnaround;
  int wait_time;
  int finish_time;
  float rat;
  bool running = false;
  bool ready = false;
};
void hrrn(queue<pro> q, int x, int l3, string l1)
{

    queue<pro> ready;

    queue<pro> temp;

    int finish[x + 1];



    struct

    {

        int val = 1000;

        int id = 0;

    } min_serv;



    char a[x][(l3 * 2) + 2];



    memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));

    a[x][(l3 * 2) + 2] = '\0';



    for (int time = 0; time < l3 + 1; time++)

    {

        if (q.front().arrive == time)

        {

            ready.push(q.front());

            temp.push(q.front());

            ready.back().ready = true;

            q.pop();

        }



        if (ready.front().service_temp == 0)

        {

            ready.front().running = false;

            finish[ready.front().pid] = time;

            ready.pop();

            min_serv.val = 0;

            for (int i = 0; i < ready.size(); i++)

            {
                ready.front().wait_time=time-ready.front().arrive;
                ready.front().rat=(ready.front().wait_time+ready.front().service)/(float)ready.front().service;

                if (ready.front().rat > min_serv.val)

                {

                    min_serv.val = ready.front().rat;

                    min_serv.id = ready.front().pid;

                    ready.push(ready.front());

                    ready.pop();

                }

                else if (ready.front().rat >= min_serv.val)

                {

                    ready.push(ready.front());

                    ready.pop();

                }

            }



            if (ready.front().pid != min_serv.id)

            {

                for (int i = 0; i < ready.size(); i++)

                {

                    if (ready.front().pid != min_serv.id) // minimum serv_remaining

                    {

                        ready.push(ready.front());

                        ready.pop();

                    }

                }

            }

        }



        // run process

        ready.front().running = true;

        ready.front().ready = false;

        ready.front().service_temp--;



        for (int j = 0; j < ready.size(); j++)

        {

            if (ready.front().running == true)

            {

                a[ready.front().pid][(time * 2) + 1] = '*';

                //  printf("%s* ", ready.front().proc_name.c_str());

                //  cout << ready.size();

            }

            else if (ready.front().ready == true)

            {

                a[ready.front().pid][(time * 2) + 1] = '.';

                //  printf("%s.", ready.front().proc_name.c_str());

            }

            // cout << endl;



            ready.push(ready.front());

            ready.pop();

        }

    }

    if (!strcmp(l1.c_str(), "trace"))

    {



        printf("HRRN  ");

        for (int i = 0; i < (l3 + 1); i++)

        {

            cout << i % 10 << " ";

        }



        cout << endl;

        cout << "------------------------------------------------" << endl;



        for (int i = 0; i < x; i++)

        {

            for (int j = 0; j < (l3 * 2) + 2; j = j + 2)

            {

                a[i][j] = '|';

            }

        }



        for (int i = 0; i < x; i++)

        {



            cout << temp.front().proc_name << "     ";

            for (int j = 0; j < (l3 * 2) + 2; j = j + 1)

            {

                cout << a[i][j];

            }

            cout << endl;

            temp.pop();

        }



        cout << "------------------------------------------------" << endl;

    }

    else if (!strcmp(l1.c_str(), "stats"))

    {

        string proc[x + 1];

        int Arrive[x + 1], serv[x + 1], turn[x + 1];

        float avg_turn = 0;

        float avg_nturn = 0;

        for (int i = 0; i < x; i++)

        {

            turn[i] = finish[i] - temp.front().arrive;

            Arrive[i] = temp.front().arrive;

            serv[i] = temp.front().service;

            proc[i] = temp.front().proc_name;

            temp.pop();

        }



        printf("HRRN");

        cout << endl;



        printf("%-11s", "Process");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3s", proc[i].c_str());

            printf("%3c", '|');

        }

        cout << endl;



        printf("%-11s", "Arrival");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", Arrive[i]);

            printf("%3c", '|');

        }

        cout << endl;



        printf("%-11s", "Service");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", serv[i]);

            printf("%3c", '|');

        }

        printf("%5s", "Mean");

        printf("|");

        cout << endl;



        printf("%-11s", "Finish");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", finish[i]);

            printf("%3c", '|');

        }

        printf("%5s", "-----");

        printf("|");

        cout << endl;



        printf("%-11s", "Turnaround");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", turn[i]);

            printf("%3c", '|');

            avg_turn += turn[i];

        }

        avg_turn /= float(x);

        printf("%5.2f", avg_turn);

        printf("|");

        cout << endl;



        printf("%-11s", "NormTurn");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%5.2f", turn[i] / float(serv[i]));

            printf("%c", '|');

            avg_nturn += turn[i] / float(serv[i]);

        }

        avg_nturn /= float(x);

        printf("%5.2f", avg_nturn);

        printf("|");

        cout << endl;

        cout << endl;

    }



}

void spn(queue<pro> q, int x, int l3, string l1)
{



    queue<pro> ready;

    queue<pro> temp;

    int finish[x + 1];



    struct

    {

        int val = 1000;

        int id = 0;

    } min_serv;



    char a[x][(l3 * 2) + 2];



    memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));

    a[x][(l3 * 2) + 2] = '\0';



    for (int time = 0; time < l3 + 1; time++)

    {

        if (q.front().arrive == time)

        {

            ready.push(q.front());

            temp.push(q.front());

            ready.back().ready = true;

            q.pop();

        }



        if (ready.front().service_temp == 0)

        {

            ready.front().running = false;

            finish[ready.front().pid] = time;

            ready.pop();

            min_serv.val = 100000;

            for (int i = 0; i < ready.size(); i++)

            {

                if (ready.front().service_temp < min_serv.val)

                {

                    min_serv.val = ready.front().service_temp;

                    min_serv.id = ready.front().pid;

                    ready.push(ready.front());

                    ready.pop();

                }

                else if (ready.front().service_temp >= min_serv.val)

                {

                    ready.push(ready.front());

                    ready.pop();

                }

            }



            if (ready.front().pid != min_serv.id)

            {

                for (int i = 0; i < ready.size(); i++)

                {

                    if (ready.front().pid != min_serv.id) // minimum serv_remaining

                    {

                        ready.push(ready.front());

                        ready.pop();

                    }

                }

            }

        }

        // else if (ready.front().service_temp != 0)

        // {

        //   ready.front().running = false;

        //   ready.push(ready.front());

        //   ready.pop();

        //   ready.back().ready = true;

        // }



        // min_serv.val = 100000;

        // for (int i = 0; i < ready.size(); i++)

        // {

        //   if (ready.front().service_temp < min_serv.val)

        //   {

        //     min_serv.val = ready.front().service_temp;

        //     min_serv.id = ready.front().pid;

        //     ready.push(ready.front());

        //     ready.pop();

        //   }

        //   else if (ready.front().service_temp >= min_serv.val)

        //   {

        //     ready.push(ready.front());

        //     ready.pop();

        //   }

        // }



        // if (ready.front().pid != min_serv.id)

        // {

        //   for (int i = 0; i < ready.size(); i++)

        //   {

        //     if (ready.front().pid != min_serv.id) // minimum serv_remaining

        //     {

        //       ready.push(ready.front());

        //       ready.pop();

        //     }

        //   }

        // }

        // run process

        ready.front().running = true;

        ready.front().ready = false;

        ready.front().service_temp--;



        for (int j = 0; j < ready.size(); j++)

        {

            if (ready.front().running == true)

            {

                a[ready.front().pid][(time * 2) + 1] = '*';

                //  printf("%s* ", ready.front().proc_name.c_str());

                //  cout << ready.size();

            }

            else if (ready.front().ready == true)

            {

                a[ready.front().pid][(time * 2) + 1] = '.';

                //  printf("%s.", ready.front().proc_name.c_str());

            }

            // cout << endl;



            ready.push(ready.front());

            ready.pop();

        }

    }

    if (!strcmp(l1.c_str(), "trace"))

    {



        printf("SPN   ");

        for (int i = 0; i < (l3 + 1); i++)

        {

            cout << i % 10 << " ";

        }



        cout << endl;

        cout << "------------------------------------------------" << endl;



        for (int i = 0; i < x; i++)

        {

            for (int j = 0; j < (l3 * 2) + 2; j = j + 2)

            {

                a[i][j] = '|';

            }

        }



        for (int i = 0; i < x; i++)

        {



            cout << temp.front().proc_name << "     ";

            for (int j = 0; j < (l3 * 2) + 2; j = j + 1)

            {

                cout << a[i][j];

            }

            cout << endl;

            temp.pop();

        }



        cout << "------------------------------------------------" << endl;

    }

    else if (!strcmp(l1.c_str(), "stats"))

    {

        string proc[x + 1];

        int Arrive[x + 1], serv[x + 1], turn[x + 1];

        float avg_turn = 0;

        float avg_nturn = 0;

        for (int i = 0; i < x; i++)

        {

            turn[i] = finish[i] - temp.front().arrive;

            Arrive[i] = temp.front().arrive;

            serv[i] = temp.front().service;

            proc[i] = temp.front().proc_name;

            temp.pop();

        }



        printf("SPN");

        cout << endl;



        printf("%-11s", "Process");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3s", proc[i].c_str());

            printf("%3c", '|');

        }

        cout << endl;



        printf("%-11s", "Arrival");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", Arrive[i]);

            printf("%3c", '|');

        }

        cout << endl;



        printf("%-11s", "Service");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", serv[i]);

            printf("%3c", '|');

        }

        printf("%5s", "Mean");

        printf("|");

        cout << endl;



        printf("%-11s", "Finish");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", finish[i]);

            printf("%3c", '|');

        }

        printf("%5s", "-----");

        printf("|");

        cout << endl;



        printf("%-11s", "Turnaround");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%3d", turn[i]);

            printf("%3c", '|');

            avg_turn += turn[i];

        }

        avg_turn /= float(x);

        printf("%5.2f", avg_turn);

        printf("|");

        cout << endl;



        printf("%-11s", "NormTurn");

        printf("|");

        for (int i = 0; i < x; i++)

        {

            printf("%5.2f", turn[i] / float(serv[i]));

            printf("%c", '|');

            avg_nturn += turn[i] / float(serv[i]);

        }

        avg_nturn /= float(x);

        printf("%5.2f", avg_nturn);

        printf("|");

        cout << endl;

        cout << endl;

    }


}

void aging(queue<pro> q, int qtime, int x, int l3, string l1)
{

  queue<pro> ready;
  queue<pro> temp;
  int finish[x + 1];
  int q_track = 0;
  struct
  {
    int val = 0;
    int id = 0;
  } min_serv;

  char a[x][(l3 * 2) + 2];

  memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));
  a[x][(l3 * 2) + 2] = '\0';

  for (int time = 0; time < l3; time++)
  {
    if (q.front().arrive == time)
    {
      ready.push(q.front());
      temp.push(q.front());
      ready.back().ready = true;
      q.pop();
    }

    if (q_track == 0)
    {

      for (int i = 0; i < ready.size(); i++)
      {
        ready.front().service_temp++;

        ready.push(ready.front());
        ready.pop();
      }

      ready.front().service_temp = ready.front().service; // ASSIGN OLD PRIORITY
      ready.front().running = false;
      ready.push(ready.front()); // OLD RUNNING PROCESS IS AT THE BACK
      ready.pop();
      ready.back().ready = true;
    }
    min_serv.val = 0;
    for (int i = 0; i < ready.size(); i++)
    {
      if (ready.front().service_temp > min_serv.val)
      {
        min_serv.val = ready.front().service_temp;
        min_serv.id = ready.front().pid;
        ready.push(ready.front());
        ready.pop();
      }
      else if (ready.front().service_temp <= min_serv.val)
      {
        ready.push(ready.front());
        ready.pop();
      }
    }

    if (ready.front().pid != min_serv.id)
    {
      for (int i = 0; i < ready.size(); i++)
      {
        if (ready.front().pid != min_serv.id) // minimum serv_remaining
        {
          ready.push(ready.front());
          ready.pop();
        }
      }
    }
    // HIGHEST PRIORITY AT FRONT OF READY
    q_track = qtime;
    ready.front().running = true;
    ready.front().ready = false;

    for (int j = 0; j < ready.size(); j++)
    {
      if (ready.front().running == true)
      {
        a[ready.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (ready.front().ready == true)
      {
        a[ready.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      ready.push(ready.front());
      ready.pop();
    }

    q_track--;
  }

  if (!strcmp(l1.c_str(), "trace"))
  {

    printf("Aging ");
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[i][j] = '|';
      }
    }

    for (int i = 0; i < x; i++)
    {

      cout << temp.front().proc_name << "     ";
      for (int j = 0; j < (l3 * 2) + 2; j = j + 1)
      {
        cout << a[i][j];
      }
      cout << endl;
      temp.pop();
    }

    cout << "------------------------------------------------" << endl;
  }
}

void FB_2i(queue<pro> q, int x, int l3, string l1)
{
  queue<pro> RQ0;
  queue<pro> RQ1;
  queue<pro> RQ2;
  queue<pro> RQ3;
  // queue<pro> RQ4;
  // queue<pro> RQ5;
  queue<pro> temp;
  int qid = 0;
  int finish[x + 1];
  int q_track = 0;
  int q0 = 1;
  int q1 = 2;
  int q2 = 4;
  int q3 = 8;
  int q4 = 16;

  char a[x][(l3 * 2) + 2];

  memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));
  a[x][(l3 * 2) + 2] = '\0';

  for (int time = 0; time < l3 + 1; time++)
  {
    if (q.front().arrive == time)
    {
      RQ0.push(q.front());
      temp.push(q.front());
      RQ0.back().ready = true;
      q.pop();
    }

    if (q_track == 0)
    {

      if (qid == 0)
      {
        if (RQ0.front().service_temp == 0)
        {
          RQ0.front().running = false;
          finish[RQ0.front().pid] = time;
          RQ0.pop();
        }
        else if (RQ0.front().service_temp != 0)
        {
          if (RQ0.size() == 1 && RQ1.empty() && RQ2.empty() && RQ3.empty())
          {
            RQ0.front().running = false;
            RQ0.front().ready = true;
          }
          else
          {
            RQ0.front().running = false;
            RQ1.push(RQ0.front());
            RQ0.pop();
            RQ1.back().ready = true;
            // cout << RQ0.size();
          }
        }
      }
      else if (qid == 1)
      {
        if (RQ1.front().service_temp == 0)
        {
          RQ1.front().running = false;
          finish[RQ1.front().pid] = time;
          RQ1.pop();
        }
        else if (RQ1.front().service_temp != 0)
        {
          if (RQ1.size() == 1 && RQ0.empty() && RQ2.empty() && RQ3.empty())
          {
            RQ1.front().running = false;
            RQ1.front().ready = true;
          }
          else
          {
            RQ1.front().running = false;
            RQ2.push(RQ1.front());
            RQ2.back().ready = true;
            RQ1.pop();
          }
        }
      }
      else if (qid == 2)
      {
        if (RQ2.front().service_temp == 0)
        {
          RQ2.front().running = false;
          finish[RQ2.front().pid] = time;
          RQ2.pop();
        }
        else if (RQ2.front().service_temp != 0)
        {
          if (RQ2.size() == 1 && RQ0.empty() && RQ1.empty() && RQ3.empty())
          {
            RQ2.front().running = false;
            RQ2.front().ready = true;
          }
          else
          {
            RQ2.front().running = false;
            RQ3.push(RQ2.front());
            RQ3.back().ready = true;
            RQ2.pop();
          }
        }
      }
      else if (qid == 3)
      {
        if (RQ3.front().service_temp == 0)
        {
          RQ3.front().running = false;
          finish[RQ3.front().pid] = time;
          RQ3.pop();
        }
        else if (RQ3.front().service_temp != 0)
        {
          if (RQ3.size() == 1 && RQ0.empty() && RQ1.empty() && RQ2.empty())
          {
            RQ3.front().running = false;
            RQ3.front().ready = true;
          }
        }
      }
    }

    if (RQ0.size() > 0 && RQ0.front().running == false && RQ1.front().running == false && RQ2.front().running == false && RQ3.front().running == false)
    {
      if (RQ0.front().service_temp <= q0)
      {
        q_track = RQ0.front().service_temp;
        RQ0.front().ready = false;
        RQ0.front().running = true;
        qid = 0;
        RQ0.front().service_temp = 0;
      }
      else if (RQ0.front().service_temp > q0)
      {
        q_track = q0;
        RQ0.front().ready = false;
        RQ0.front().running = true;
        qid = 0;
        RQ0.front().service_temp -= q0;
      }
    }

    else if (RQ1.size() > 0 && RQ0.empty() && RQ0.front().running == false && RQ1.front().running == false && RQ2.front().running == false && RQ3.front().running == false)
    {

      if (RQ1.front().service_temp <= 2)
      {
        q_track = RQ1.front().service_temp;
        RQ1.front().ready = false;
        RQ1.front().running = true;
        qid = 1;
        RQ1.front().service_temp = 0;
      }
      else if (RQ1.front().service_temp > 2)
      {
        q_track = 2;
        RQ1.front().ready = false;
        RQ1.front().running = true;
        qid = 1;
        RQ1.front().service_temp -= 2;
      }
    }

    else if (RQ2.size() > 0 && RQ0.empty() && RQ1.empty() && RQ0.front().running == false && RQ1.front().running == false && RQ2.front().running == false && RQ3.front().running == false)
    {

      if (RQ2.front().service_temp <= q2)
      {
        q_track = RQ2.front().service_temp;
        RQ2.front().ready = false;
        RQ2.front().running = true;
        qid = 2;
        RQ2.front().service_temp = 0;
      }
      else if (RQ2.front().service_temp > q2)
      {
        q_track = q2;
        RQ2.front().ready = false;
        RQ2.front().running = true;
        qid = 2;
        RQ2.front().service_temp -= q2;
      }
    }

    else if (RQ3.size() > 0 && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ0.front().running == false && RQ1.front().running == false && RQ2.front().running == false && RQ3.front().running == false)
    {

      if (RQ3.front().service_temp <= q3)
      {
        q_track = RQ3.front().service_temp;
        RQ3.front().ready = false;
        RQ3.front().running = true;
        qid = 3;
        RQ3.front().service_temp = 0;
      }
      else if (RQ3.front().service_temp > q3)
      {
        q_track = q3;
        RQ3.front().ready = false;
        RQ3.front().running = true;
        qid = 3;
        RQ3.front().service_temp -= q3;
      }
    }

    for (int j = 0; j < (RQ0.size()); j++)
    {

      if (RQ0.front().running == true)
      {
        a[RQ0.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ0.front().ready == true)
      {
        a[RQ0.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ0.push(RQ0.front());
      RQ0.pop();
    } //+RQ1.size()+RQ2.size()+RQ3.size()+RQ4.size()
    for (int j = 0; j < (RQ1.size()); j++)
    {
      if (RQ1.front().running == true)
      {
        a[RQ1.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ1.front().ready == true)
      {
        a[RQ1.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ1.push(RQ1.front());
      RQ1.pop();
    }
    for (int j = 0; j < (RQ2.size()); j++)
    {
      if (RQ2.front().running == true)
      {
        a[RQ2.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ2.front().ready == true)
      {
        a[RQ2.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ2.push(RQ2.front());
      RQ2.pop();
    }
    for (int j = 0; j < (RQ3.size()); j++)
    {
      if (RQ3.front().running == true)
      {
        a[RQ3.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ3.front().ready == true)
      {
        a[RQ3.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ3.push(RQ3.front());
      RQ3.pop();
    }

    q_track--;
  }

  if (!strcmp(l1.c_str(), "trace"))
  {
    printf("FB-2i ");
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[i][j] = '|';
      }
    }

    for (int i = 0; i < x; i++)
    {

      cout << temp.front().proc_name << "     ";
      for (int j = 0; j < (l3 * 2) + 2; j = j + 1)
      {
        cout << a[i][j];
      }
      cout << endl;
      temp.pop();
    }

    cout << "------------------------------------------------" << endl;
  }
  else if (!strcmp(l1.c_str(), "stats"))
  {
    string proc[x + 1];
    int Arrive[x + 1], serv[x + 1], turn[x + 1];
    float avg_turn = 0;
    float avg_nturn = 0;
    for (int i = 0; i < x; i++)
    {
      turn[i] = finish[i] - temp.front().arrive;
      Arrive[i] = temp.front().arrive;
      serv[i] = temp.front().service;
      proc[i] = temp.front().proc_name;
      temp.pop();
    }

    printf("FB-2i");
    cout << endl;

    printf("%-11s", "Process");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3s", proc[i].c_str());
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Arrival");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", Arrive[i]);
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Service");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", serv[i]);
      printf("%3c", '|');
    }
    printf("%5s", "Mean");
    printf("|");
    cout << endl;

    printf("%-11s", "Finish");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", finish[i]);
      printf("%3c", '|');
    }
    printf("%5s", "-----");
    printf("|");
    cout << endl;

    printf("%-11s", "Turnaround");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", turn[i]);
      printf("%3c", '|');
      avg_turn += turn[i];
    }
    avg_turn /= float(x);
    printf("%5.2f", avg_turn);
    printf("|");
    cout << endl;

    printf("%-11s", "NormTurn");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%5.2f", turn[i] / float(serv[i]));
      printf("%c", '|');
      avg_nturn += turn[i] / float(serv[i]);
    }
    avg_nturn /= float(x);
    printf("%5.2f", avg_nturn);
    printf("|");
    cout << endl;
    cout << endl;
  }
}

void FB_1(queue<pro> q, int x, int l3, string l1)
{
  queue<pro> RQ0;
  queue<pro> RQ1;
  queue<pro> RQ2;
  queue<pro> RQ3;
  queue<pro> RQ4;
  queue<pro> RQ5;
  queue<pro> temp;
  int qid = 0;
  int finish[x + 1];

  char a[x][(l3 * 2) + 2];

  memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));
  a[x][(l3 * 2) + 2] = '\0';

  for (int time = 0; time < l3 + 1; time++)
  {
    if (q.front().arrive == time)
    {
      RQ0.push(q.front());
      temp.push(q.front());
      RQ0.back().ready = true;
      q.pop();
    }

    if (qid == 0)
    {
      if (RQ0.front().service_temp == 0)
      {
        RQ0.front().running = false;
        finish[RQ0.front().pid] = time;
        RQ0.pop();
      }
      else if (RQ0.front().service_temp != 0)
      {
        if (RQ0.size() == 1 && RQ4.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() && RQ5.empty())
        {
        }
        else
        {
          RQ0.front().running = false;
          RQ1.push(RQ0.front());
          RQ0.pop();
          RQ1.back().ready = true;
          // cout << RQ0.size();
        }
      }
    }
    else if (qid == 1)
    {
      if (RQ1.front().service_temp == 0)
      {
        RQ1.front().running = false;
        finish[RQ1.front().pid] = time;
        RQ1.pop();
      }
      else if (RQ1.front().service_temp != 0)
      {
        if (RQ1.size() == 1 && RQ4.empty() && RQ0.empty() && RQ2.empty() && RQ3.empty() && RQ5.empty())
        {
        }
        else
        {
          RQ1.front().running = false;
          RQ2.push(RQ1.front());
          RQ2.back().ready = true;
          RQ1.pop();
        }
      }
    }
    else if (qid == 2)
    {
      if (RQ2.front().service_temp == 0)
      {
        RQ2.front().running = false;
        finish[RQ2.front().pid] = time;
        RQ2.pop();
      }
      else if (RQ2.front().service_temp != 0)
      {
        if (RQ2.size() == 1 && RQ4.empty() && RQ0.empty() && RQ1.empty() && RQ3.empty() && RQ5.empty())
        {
        }
        else
        {
          RQ2.front().running = false;
          RQ3.push(RQ2.front());
          RQ3.back().ready = true;
          RQ2.pop();
        }
      }
    }
    else if (qid == 3)
    {
      if (RQ3.front().service_temp == 0)
      {
        RQ3.front().running = false;
        finish[RQ3.front().pid] = time;
        RQ3.pop();
      }
      else if (RQ3.front().service_temp != 0)
      {
        if (RQ3.size() == 1 && RQ4.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ5.empty())
        {
        }
        else
        {
          RQ3.front().running = false;
          RQ4.push(RQ3.front());
          RQ4.back().ready = true;
          RQ3.pop();
        }
      }
    }
    else if (qid == 4)
    {
      if (RQ4.front().service_temp == 0)
      {
        RQ4.front().running = false;
        finish[RQ4.front().pid] = time;
        RQ4.pop();
      }
      else if (RQ4.front().service_temp != 0)
      {
        if (RQ4.size() == 1 && RQ3.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ5.empty())
        {
        }
        else
        {
          RQ4.front().running = false;
          RQ5.push(RQ4.front());
          RQ5.back().ready = true;
          RQ4.pop();
        }
      }
    }
    else if (qid == 5)
    {
      if (RQ5.front().service_temp == 0)
      {
        RQ5.front().running = false;
        finish[RQ5.front().pid] = time;
        RQ5.pop();
      }
      else if (RQ5.front().service_temp != 0)
      {
        if (RQ5.size() == 1 && RQ3.empty() && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ4.empty())
        {
        }
      }
    }

    if (RQ0.size() > 0)
    {
      RQ0.front().ready = false;
      RQ0.front().running = true;
      qid = 0;
      RQ0.front().service_temp--;
    }

    else if (RQ1.size() > 0 && RQ0.empty())
    {

      RQ1.front().ready = false;
      RQ1.front().running = true;
      qid = 1;
      RQ1.front().service_temp--;
    }

    else if (RQ2.size() > 0 && RQ0.empty() && RQ1.empty())
    {

      RQ2.front().ready = false;
      RQ2.front().running = true;
      qid = 2;
      RQ2.front().service_temp--;
    }

    else if (RQ3.size() > 0 && RQ0.empty() && RQ1.empty() && RQ2.empty())
    {

      RQ3.front().ready = false;
      RQ3.front().running = true;
      qid = 3;
      RQ3.front().service_temp--;
    }
    else if (RQ4.size() > 0 && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty())
    {
      RQ4.front().ready = false;
      RQ4.front().running = true;
      qid = 4;
      RQ4.front().service_temp--;
    }
    else if (RQ5.size() > 0 && RQ0.empty() && RQ1.empty() && RQ2.empty() && RQ3.empty() && RQ4.empty())
    {
      RQ5.front().ready = false;
      RQ5.front().running = true;
      qid = 5;
      RQ5.front().service_temp--;
    }

    for (int j = 0; j < (RQ0.size()); j++)
    {

      if (RQ0.front().running == true)
      {
        a[RQ0.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ0.front().ready == true)
      {
        a[RQ0.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ0.push(RQ0.front());
      RQ0.pop();
    } //+RQ1.size()+RQ2.size()+RQ3.size()+RQ4.size()
    for (int j = 0; j < (RQ1.size()); j++)
    {
      if (RQ1.front().running == true)
      {
        a[RQ1.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ1.front().ready == true)
      {
        a[RQ1.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ1.push(RQ1.front());
      RQ1.pop();
    }
    for (int j = 0; j < (RQ2.size()); j++)
    {
      if (RQ2.front().running == true)
      {
        a[RQ2.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ2.front().ready == true)
      {
        a[RQ2.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ2.push(RQ2.front());
      RQ2.pop();
    }
    for (int j = 0; j < (RQ3.size()); j++)
    {
      if (RQ3.front().running == true)
      {
        a[RQ3.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ3.front().ready == true)
      {
        a[RQ3.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ3.push(RQ3.front());
      RQ3.pop();
    }

    for (int j = 0; j < (RQ4.size()); j++)
    {
      if (RQ4.front().running == true)
      {
        a[RQ4.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ4.front().ready == true)
      {
        a[RQ4.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ4.push(RQ4.front());
      RQ4.pop();
    }
    for (int j = 0; j < (RQ5.size()); j++)
    {
      if (RQ5.front().running == true)
      {
        a[RQ5.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (RQ5.front().ready == true)
      {
        a[RQ5.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      RQ5.push(RQ5.front());
      RQ5.pop();
    }
  }
  if (!strcmp(l1.c_str(), "trace"))
  {
    printf("FB-1  ");
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[i][j] = '|';
      }
    }

    for (int i = 0; i < x; i++)
    {

      cout << temp.front().proc_name << "     ";
      for (int j = 0; j < (l3 * 2) + 2; j = j + 1)
      {
        cout << a[i][j];
      }
      cout << endl;
      temp.pop();
    }

    cout << "------------------------------------------------" << endl;
  }
  else if (!strcmp(l1.c_str(), "stats"))
  {
    string proc[x + 1];
    int Arrive[x + 1], serv[x + 1], turn[x + 1];
    float avg_turn = 0;
    float avg_nturn = 0;
    for (int i = 0; i < x; i++)
    {
      turn[i] = finish[i] - temp.front().arrive;
      Arrive[i] = temp.front().arrive;
      serv[i] = temp.front().service;
      proc[i] = temp.front().proc_name;
      temp.pop();
    }

    printf("FB-1");
    cout << endl;

    printf("%-11s", "Process");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3s", proc[i].c_str());
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Arrival");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", Arrive[i]);
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Service");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", serv[i]);
      printf("%3c", '|');
    }
    printf("%5s", "Mean");
    printf("|");
    cout << endl;

    printf("%-11s", "Finish");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", finish[i]);
      printf("%3c", '|');
    }
    printf("%5s", "-----");
    printf("|");
    cout << endl;

    printf("%-11s", "Turnaround");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", turn[i]);
      printf("%3c", '|');
      avg_turn += turn[i];
    }
    avg_turn /= float(x);
    printf("%5.2f", avg_turn);
    printf("|");
    cout << endl;

    printf("%-11s", "NormTurn");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%5.2f", turn[i] / float(serv[i]));
      printf("%c", '|');
      avg_nturn += turn[i] / float(serv[i]);
    }
    avg_nturn /= float(x);
    printf("%5.2f", avg_nturn);
    printf("|");
    cout << endl;
    cout << endl;
  }
}

void SRT(queue<pro> q, int x, int l3, string l1)
{
  queue<pro> ready;
  queue<pro> temp;
  int finish[x + 1];

  struct
  {
    int val = 1000;
    int id = 0;
  } min_serv;

  char a[x][(l3 * 2) + 2];

  memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));
  a[x][(l3 * 2) + 2] = '\0';

  for (int time = 0; time < l3 + 1; time++)
  {
    if (q.front().arrive == time)
    {
      ready.push(q.front());
      temp.push(q.front());
      ready.back().ready = true;
      q.pop();
    }

    if (ready.front().service_temp == 0)
    {
      ready.front().running = false;
      finish[ready.front().pid] = time;
      ready.pop();
    }
    else if (ready.front().service_temp != 0)
    {
      ready.front().running = false;
      ready.push(ready.front());
      ready.pop();
      ready.back().ready = true;
    }
    // ready.front().running=false;
    // ready.push(ready.front());
    // ready.back().ready=true;
    min_serv.val = 100000;
    for (int i = 0; i < ready.size(); i++)
    {
      if (ready.front().service_temp < min_serv.val)
      {
        min_serv.val = ready.front().service_temp;
        min_serv.id = ready.front().pid;
        ready.push(ready.front());
        ready.pop();
      }
      else if (ready.front().service_temp >= min_serv.val)
      {
        ready.push(ready.front());
        ready.pop();
      }
    }

    if (ready.front().pid != min_serv.id)
    {
      for (int i = 0; i < ready.size(); i++)
      {
        if (ready.front().pid != min_serv.id) // minimum serv_remaining
        {
          ready.push(ready.front());
          ready.pop();
        }
      }
    }
    // run process
    ready.front().running = true;
    ready.front().ready = false;
    ready.front().service_temp--;

    for (int j = 0; j < ready.size(); j++)
    {
      if (ready.front().running == true)
      {
        a[ready.front().pid][(time * 2) + 1] = '*';
        //  printf("%s* ", ready.front().proc_name.c_str());
        //  cout << ready.size();
      }
      else if (ready.front().ready == true)
      {
        a[ready.front().pid][(time * 2) + 1] = '.';
        //  printf("%s.", ready.front().proc_name.c_str());
      }
      // cout << endl;

      ready.push(ready.front());
      ready.pop();
    }
  }
  if (!strcmp(l1.c_str(), "trace"))
  {

    printf("SRT   ");
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[i][j] = '|';
      }
    }

    for (int i = 0; i < x; i++)
    {

      cout << temp.front().proc_name << "     ";
      for (int j = 0; j < (l3 * 2) + 2; j = j + 1)
      {
        cout << a[i][j];
      }
      cout << endl;
      temp.pop();
    }

    cout << "------------------------------------------------" << endl;
  }
  else if (!strcmp(l1.c_str(), "stats"))
  {
    string proc[x + 1];
    int Arrive[x + 1], serv[x + 1], turn[x + 1];
    float avg_turn = 0;
    float avg_nturn = 0;
    for (int i = 0; i < x; i++)
    {
      turn[i] = finish[i] - temp.front().arrive;
      Arrive[i] = temp.front().arrive;
      serv[i] = temp.front().service;
      proc[i] = temp.front().proc_name;
      temp.pop();
    }

    printf("SRT");
    cout << endl;

    printf("%-11s", "Process");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3s", proc[i].c_str());
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Arrival");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", Arrive[i]);
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Service");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", serv[i]);
      printf("%3c", '|');
    }
    printf("%5s", "Mean");
    printf("|");
    cout << endl;

    printf("%-11s", "Finish");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", finish[i]);
      printf("%3c", '|');
    }
    printf("%5s", "-----");
    printf("|");
    cout << endl;

    printf("%-11s", "Turnaround");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", turn[i]);
      printf("%3c", '|');
      avg_turn += turn[i];
    }
    avg_turn /= float(x);
    printf("%5.2f", avg_turn);
    printf("|");
    cout << endl;

    printf("%-11s", "NormTurn");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%5.2f", turn[i] / float(serv[i]));
      printf("%c", '|');
      avg_nturn += turn[i] / float(serv[i]);
    }
    avg_nturn /= float(x);
    printf("%5.2f", avg_nturn);
    printf("|");
    cout << endl;
    cout << endl;
  }
}


void RoundRobin(queue<pro> q, int qtime, int x, int l3, string l1)
{
  queue<pro> ready;
  queue<pro> temp;
  int q_track = 0;
  int finish[x + 1];

  char a[x][(l3 * 2) + 2];

  memset(a, ' ', sizeof(a[x][(l3 * 2) + 2]) * x * ((l3 * 2) + 2));
  a[x][(l3 * 2) + 2] = '\0';

  for (int iii = 0; iii < l3 + 1; iii++)
  {
    if (q.front().arrive == iii)
    {
      ready.push(q.front());
      temp.push(q.front());
      ready.back().ready = true;
      q.pop();
    }

    if (q_track == 0)
    {
      if (ready.front().service_temp == 0)
      {
        ready.front().running = false;
        finish[ready.front().pid] = iii;
        ready.pop();
      }
      else if (ready.front().service_temp != 0)
      {
        ready.front().running = false;
        ready.front().ready = true;
        ready.push(ready.front());
        ready.pop();
      }
    }

    if (ready.front().service_temp <= qtime && ready.front().running == false)
    {
      q_track = ready.front().service_temp;
      ready.front().running = true;
      ready.front().ready = false;
      ready.front().service_temp = 0;
    }
    else if (ready.front().service_temp > qtime && ready.front().running == false)
    {
      q_track = qtime;
      ready.front().running = true;
      ready.front().ready = false;
      ready.front().service_temp -= qtime;
    }

    for (int j = 0; j < ready.size(); j++)
    {
      if (ready.front().running == true)
      {
        a[ready.front().pid][(iii * 2) + 1] = '*';
        // printf("%s*", ready.front().proc_name.c_str());
      }
      else if (ready.front().ready == true)
      {
        a[ready.front().pid][(iii * 2) + 1] = '.';
        // printf("%s.", ready.front().proc_name.c_str());
      }

      ready.push(ready.front());
      ready.pop();
    }

    q_track--;
  }

  if (!strcmp(l1.c_str(), "trace"))
  {

    printf("RR-%-3d", qtime);
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < x; i++)
    {
      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[i][j] = '|';
      }
    }

    for (int i = 0; i < x; i++)
    {

      cout << temp.front().proc_name << "     ";
      for (int j = 0; j < (l3 * 2) + 2; j = j + 1)
      {
        cout << a[i][j];
      }
      cout << endl;
      temp.pop();
    }

    cout << "------------------------------------------------" << endl;
  }

  else if (!strcmp(l1.c_str(), "stats"))
  {
    string proc[x + 1];
    int Arrive[x + 1], serv[x + 1], turn[x + 1];
    float avg_turn = 0;
    float avg_nturn = 0;
    for (int i = 0; i < x; i++)
    {
      turn[i] = finish[i] - temp.front().arrive;
      Arrive[i] = temp.front().arrive;
      serv[i] = temp.front().service;

      proc[i] = temp.front().proc_name;
      temp.pop();
    }

    printf("RR-%d", qtime);
    cout << endl;

    printf("%-11s", "Process");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3s", proc[i].c_str());
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Arrival");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", Arrive[i]);
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Service");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", serv[i]);
      printf("%3c", '|');
    }
    printf("%5s", "Mean");
    printf("|");
    cout << endl;

    printf("%-11s", "Finish");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", finish[i]);
      printf("%3c", '|');
    }
    printf("%5s", "-----");
    printf("|");
    cout << endl;

    printf("%-11s", "Turnaround");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", turn[i]);
      printf("%3c", '|');
      avg_turn += turn[i];
    }
    avg_turn /= float(x);
    printf("%5.2f", avg_turn);
    printf("|");
    cout << endl;

    printf("%-11s", "NormTurn");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%5.2f", turn[i] / float(serv[i]));
      printf("%c", '|');
      avg_nturn += turn[i] / float(serv[i]);
    }
    avg_nturn /= float(x);
    printf("%5.2f", avg_nturn);
    printf("|");
    cout << endl;
    cout << endl;
  }
}

void FCFS(queue<pro> q, int x, int l3, string l1) // x is num of process
{
  if (!strcmp(l1.c_str(), "trace"))
  {
    cout << "FCFS  ";
    for (int i = 0; i < (l3 + 1); i++)
    {
      cout << i % 10 << " ";
    }

    cout << endl;
    cout << "------------------------------------------------" << endl;

    char a[(l3 * 2) + 2];

    memset(a, ' ', (l3 * 2) + 2);
    a[(l3 * 2) + 2] = '\0';

    for (int i = 0; i < x; i++)
    {

      cout << q.front().proc_name << "     ";

      // ready states
      for (int j = 1; j <= (l3 * 2) + 2; j = j + 1)
      {
        if (j >= (q.front().arrive) + 1 && j < q.front().wait_time + 1)
        {

          a[(2 * j) - 1] = '.';
        }
      }

      // running
      for (int j = 0; j <= (l3 * 2) + 2; j = j + 1)
      {
        if (j >= q.front().wait_time && j < (q.front().finish_time))
        {

          a[(2 * j) + 1] = '*';
        }
      }

      for (int j = 0; j < (l3 * 2) + 2; j = j + 2)
      {
        a[j] = '|';
      }

      for (int y = 0; y < (l3 * 2) + 2; y++)
      {
        cout << a[y];
      }
      // Free array
      memset(a, ' ', (l3 * 2) + 2);
      a[(l3 * 2) + 2] = '\0';
      q.pop();
      cout << endl;
    }

    cout << "------------------------------------------------" << endl;
  }
  else if (!strcmp(l1.c_str(), "stats"))
  {
    string proc[x + 1];
    int Arrive[x + 1], serv[x + 1], finish[x + 1], turn[x + 1];
    float avg_turn = 0;
    float avg_nturn = 0;
    for (int i = 0; i < x; i++)
    {
      Arrive[i] = q.front().arrive;
      serv[i] = q.front().service;
      finish[i] = q.front().finish_time;
      turn[i] = q.front().turnaround;
      proc[i] = q.front().proc_name;
      q.pop();
    }

    cout << "FCFS";
    cout << endl;

    printf("%-11s", "Process");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3s", proc[i].c_str());
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Arrival");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", Arrive[i]);
      printf("%3c", '|');
    }
    cout << endl;

    printf("%-11s", "Service");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", serv[i]);
      printf("%3c", '|');
    }
    printf("%5s", "Mean");
    printf("|");
    cout << endl;

    printf("%-11s", "Finish");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", finish[i]);
      printf("%3c", '|');
    }
    printf("%5s", "-----");
    printf("|");
    cout << endl;

    printf("%-11s", "Turnaround");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%3d", turn[i]);
      printf("%3c", '|');
      avg_turn += turn[i];
    }
    avg_turn /= float(x);
    printf("%5.2f", avg_turn);
    printf("|");
    cout << endl;

    printf("%-11s", "NormTurn");
    printf("|");
    for (int i = 0; i < x; i++)
    {
      printf("%5.2f", turn[i] / float(serv[i]));
      printf("%c", '|');
      avg_nturn += turn[i] / float(serv[i]);
    }
    avg_nturn /= float(x);
    printf("%5.2f", avg_nturn);
    printf("|");
    cout << endl;
    cout << endl;
  }
}

int main()
{
  ifstream file;
  string l1;
  string algo_num_q;
  string temp;
  string subs;
  // int algo_num[10];
  // int quantum[10];
  int algo_num;
  int quantum;
  int l3; // last time
  int number_of_processes;
  int num;
  int id = 0;
  int tr=0;
  vector<string> v;
  queue<pro> q;
  vector<int> num_q;
  vector<string> xx;

  // file.open("01a-input.txt");
  file.open("hello.txt");

    cin >> l1;
    cin >> algo_num_q;
    cin >> l3;
    cin >> number_of_processes;
    num = number_of_processes;



 
     istringstream tokenStream(algo_num_q);
     while (getline(tokenStream, temp, '-'))
     {
       num_q.push_back(stoi(temp));
     }
     algo_num = num_q[0];
     quantum = num_q[1];

    while (num--)
    {
      int last_wait, last_serv;
      pro p1;
      string line;
      cin >> line;
      stringstream ss(line);
      while (ss.good())
      {
        string sub;
        getline(ss, sub, ',');
        v.push_back(sub);
      }

      p1.proc_name = v[0];
      p1.pid = q.size();
      p1.arrive = stoi(v[1]);
      p1.service = stoi(v[2]);
      p1.service_temp = p1.service;

      if (q.size() == 0)
      {
        p1.wait_time = 0;
      }
      else
      {
        p1.wait_time = last_wait + last_serv;
      }

      p1.finish_time = p1.service + p1.wait_time;
      p1.turnaround = p1.finish_time - p1.arrive;
      last_wait = p1.wait_time;
      last_serv = p1.service;
      q.push(p1);

      v.clear();
    }
    // cout << q.size();
    //  cout<<"size of Queue is : "<<q.size();
  






  switch (algo_num)
  {
  case 1:

    FCFS(q, number_of_processes, l3, l1);
    break;
  case 2:
    RoundRobin(q, quantum, number_of_processes, l3, l1);
    break;
     break;
    case 3:
        spn(q, number_of_processes, l3, l1);
        break;

   case 4:
    SRT(q, number_of_processes, l3, l1);
    break;

    case 5:
        hrrn(q, number_of_processes, l3, l1);
        break;

  case 6:
    FB_1(q, number_of_processes, l3, l1);
    break;
  case 7:
    FB_2i(q, number_of_processes, l3, l1);
    break;
  case 8:
    aging(q, quantum, number_of_processes, l3, l1);
    break;
  }


  file.close();
  return 0;
}
