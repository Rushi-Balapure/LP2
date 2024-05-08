def get_user_input(symptoms):
    user_symptoms = []
    for symptom in symptoms:
        response = input("Do you have " + symptom + "? (y/n): ")
        if response.lower() == 'y':
            user_symptoms.append(symptom)
    return user_symptoms

def get_weighted_symptoms(user_symptoms, symptoms_weights):
    weighted_symptoms = {}
    for symptom in user_symptoms:
        weighted_symptoms[symptom] = symptoms_weights.get(symptom, 0)
    return weighted_symptoms

def diagnose_patient():
    symptoms = ["Fever", "Cough", "Headache", "Sore throat", "Shortness of breath", "Chest pain", "Fatigue", "Nausea", "Vomiting", "Dehydration", "Increased thirst", "Blurred vision", "Weight loss", "Abdominal Cramps"]

    symptoms_weights = {
        "Fever": 1,
        "Cough": 0.5,
        "Headache": 0.7,
        "Sore throat": 0.6,
        "Shortness of breath": 1.2,
        "Chest pain": 1.5,
        "Fatigue": 0.8,
        "Nausea": 0.7,
        "Vomiting": 0.9,
        "Dehydration": 1.3,
        "Increased thirst": 0.8,
        "Blurred vision": 1.1,
        "Weight loss": 1.4,
        "Abdominal Cramps": 0.9
    }

    diseases = {
        "Common Cold": ["Fever", "Cough", "Headache", "Sore throat"],
        "Flu": ["Fever", "Cough", "Headache"],
        "Strep Throat": ["Fever", "Sore throat"],
        "Migraine": ["Headache"],
        "Pneumonia": ["Fever", "Cough", "Shortness of breath", "Chest pain", "Fatigue", "Confusion", "Nausea", "Vomiting"],
        "Gastroenteritis": ["Diarrhea", "Nausea", "Vomiting", "Abdominal cramps", "Fever", "Blood in stool", "Dehydration"],
        "Diabetes": ["Increased thirst", "Frequent urination", "Extreme hunger", "Unexplained weight loss", "Fatigue", "Irritability", "Blurred vision", "Slow-healing sores"],
        "Hypertension": ["Headaches", "Shortness of breath", "Nosebleeds", "Dizziness", "Chest pain", "Vision changes"],
        "Otitis Media (Ear Infection)": ["Ear pain", "Tugging or pulling at the ear", "Difficulty sleeping", "Fussiness in infants and young children", "Fever", "Fluid drainage from the ear"],
        "Meningitis": ["Sudden high fever", "Stiff neck", "Severe headache", "Headache with nausea or vomiting", "Confusion or difficulty concentrating", "Seizures", "Sleepiness or difficulty waking up", "Sensitivity to light"],
        "Hyperthyroidism": ["Weight loss", "Rapid heartbeat (tachycardia)", "Irregular heartbeat (arrhythmia)", "Increased appetite", "Nervousness", "Anxiety", "Irritability", "Tremor (shaking) in hands and fingers", "Sweating"]
    }

    doctor_recommendations = {
        "General Practitioner (GP)": ["Common Cold", "Flu", "Strep Throat", "Pneumonia", "Urinary Tract Infection (UTI)", "Gastroenteritis", "Hypertension", "Otitis Media (Ear Infection)"],
        "Pulmonologist": ["Pneumonia"],
        "Gastroenterologist": ["Gastroenteritis"],
        "Endocrinologist": ["Diabetes", "Hyperthyroidism"],
        "Neurologist": ["Migraine", "Meningitis"],
        "ENT Specialist": ["Strep Throat", "Otitis Media (Ear Infection)"],
        "Cardiologist": ["Hypertension"]
    }

    user_symptoms = get_user_input(symptoms)
    weighted_symptoms = get_weighted_symptoms(user_symptoms, symptoms_weights)
    possible_diseases = set()

    for symptom, weight in weighted_symptoms.items():
        for disease, causes in diseases.items():
            if symptom in causes:
                possible_diseases.add(disease)

    if possible_diseases:
        print("Possible diseases:")
        for disease_name in possible_diseases:
            print("- " + disease_name)

        # Find the most probable disease based on the weighted sum of symptoms
        most_probable_disease = ""
        max_weighted_sum = 0
        for disease_name in possible_diseases:
            weighted_sum = sum(weighted_symptoms[symptom] for symptom in diseases[disease_name])
            if weighted_sum > max_weighted_sum:
                most_probable_disease = disease_name
                max_weighted_sum = weighted_sum

        print("\nMost probable disease based on symptoms:", most_probable_disease)

        # Find recommended doctor for the most probable disease
        print("\nRecommended doctor(s) to consult for the most probable disease:")
        for doctor, specialties in doctor_recommendations.items():
            if most_probable_disease in specialties:
                print("- " + doctor)
    else:
        print("No matching diseases found.")

diagnose_patient()
