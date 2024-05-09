import json
from difflib import get_close_matches

def load_knowlegde_base(file_path):
    with open(file_path,"r") as file :
        data = json.load(file) 
    return data 

def save_knowledge_base(file_path,data):
    with open(file_path,"w") as file :
        json.dump(data,file,indent=2)

def find_best_match(user_question,questions):
    matches = get_close_matches(user_question,questions,n=1,cutoff=0.6)
    if(matches):
        return matches[0]
    else:
        return None

def get_answer_for_question(question,knowledge_base):
    for q in knowledge_base["questions"]:
        if(q["question"] == question):
            return q["answer"]
        
def chat_bot():
    knowledge_base = load_knowlegde_base("Assignment 7/knowledge_base.json")
    while True :
        user_input = input("\nUser: ")
        if(user_input.lower() == "quit"):
            break
        best_match = find_best_match(user_input.lower(),[q["question"] for q in knowledge_base["questions"]])

        if(best_match):
            answer = get_answer_for_question(best_match,knowledge_base)
            print("\nBot : ",answer,end="")
        else :
            print("\nSorry! I couldn't understand what you meant. could you help me")
            new_answer = input("type the answer or type 'skip' to skip: ")

            if(new_answer.lower() != "skip"):
                knowledge_base["questions"].append({"question":user_input,"answer":new_answer})
                save_knowledge_base("Assignment 7/knowledge_base.json",knowledge_base)
                print("Bot : Thank you I have learned it ")


chat_bot()