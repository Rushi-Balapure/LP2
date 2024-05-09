#include <iostream>
#include <vector>
// #include <algorithm>

using namespace std ; 

struct job{
    int id ; 
    int dead ; 
    int profit ;
};

bool comparison(job a, job b){
    return (a.profit > b.profit) ;
}

void printJobSchedule(vector<job> jobs){
    sort(jobs.begin() , jobs.end() ,comparison) ;
    int n = jobs.size();
    vector<job> result ; 
    vector<bool> slot (jobs.size(),false); 

    for(int i = 0 ; i < n ; i ++){
        for(int j = min(n, jobs[i].dead -1) ; j >= 0 ; j --){
            if(slot[j] == false){
                result.push_back(jobs[i]);
                slot[j] = true ;
                break ;
            }
        }
    }

    for (int i = 0 ; i < n ; i ++){
        if(slot[i]){
            cout<<(char)result[i].id<<" ";
        }
    }


}

int main (){
    vector<job> jobs ; 
    job job1 = {'a',2,100} ;
    jobs.push_back(job1);
    job job2 = {'b',1,19} ;
    jobs.push_back(job2);
    job job3 = {'c',2,27};
    jobs.push_back(job3);
    job job4 = {'d',1,25} ;
    jobs.push_back(job4);
    job job5 = {'e',3,15} ;
    jobs.push_back(job5);

    printJobSchedule(jobs);
}
