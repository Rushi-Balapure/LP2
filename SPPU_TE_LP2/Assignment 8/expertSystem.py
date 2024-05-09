symptoms = ['Fever', 'Cough', 'Headache', 'Sore throat']
diseases = {
    'Common Cold': ['Fever', 'Cough', 'Headache', 'Sore throat'],
    'Flu': ['Fever', 'Cough', 'Headache'],
    'Strep Throat': ['Fever', 'Sore throat'],
    'Migraine': ['Headache']
}


def get_user_input():
    user_symptoms = []
    for symptom in symptoms:
        response = input(f"Do you have {symptom}? (y/n): ")
        if response.lower() == 'y':
            user_symptoms.append(symptom)
    return user_symptoms


def diagnose():
    user_symptoms = get_user_input()
    possible_diseases = []

    for disease_name, symptoms in diseases.items():
        if any(symptom in user_symptoms for symptom in symptoms):
            possible_diseases.append(disease_name)

    if possible_diseases:
        print("Possible diseases:")
        for disease_name in possible_diseases:
            print("- " + disease_name)
    else:
        print("No matching diseases found.")


diagnose()