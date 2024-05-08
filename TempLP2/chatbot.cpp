#include <iostream>
#include <vector>
#include <map>
#include <string>  // Add this line
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

string toLowercase(string s) {
    for (char& c : s) {
        c = tolower(c);
    }
    return s;
}

string greet() {
    // Initialize random seed
    srand(time(0));

    vector<string> greetings = {
        "Hello! Welcome to Myntra customer service. How can I assist you today?",
        "Hi there! Are you looking for information about a product or need help with your order?"
    };

    int index = rand() % greetings.size();
    return greetings[index];
}

string answer(string question) {
    // Responses to different types of questions
    map<string, string> responses = {
        {"delivery times", "Delivery times typically range from {min_days} to {max_days} business days depending on your location and chosen shipping option. You can find more details on the product page."},
        {"return an item", "For hassle-free returns, you can visit our Returns Center at our official website."},
        {"track my order", "Absolutely! You can track your order by signing in to your Myntra account and going to 'Your Orders'."},
        {"specific product", "Sure, tell me more about the product you're interested in. What's the name or do you have a link?"},
        {"speak to a representative", "I understand. While I can answer most questions, you can connect with a live representative through our online chat option on the Myntra website."},
        {"order status", "To check your order status, can I get your order number?"},
        {"return the item", "For return requests, please visit our Returns & Exchanges page on the Myntra website."},
        {"size chart", "You can refer to our size guide available on the product page to find the perfect fit."},
        {"discount going on", "Hello there! You will find details of discount and sales on homepage or while purchasing the product."},
        {"complaint regarding item", "I'm sorry to hear that. Please share your concern, and I'll do my best to assist you."}
    };

    string bestMatch;
    int bestMatchScore = 0;
    for (auto const& res : responses) {
        string key = res.first;
        string value = res.second;
        int score = 0;
        string lowercaseQuestion = toLowercase(question);
        string lowercaseKey = toLowercase(key);
        size_t pos = lowercaseQuestion.find(lowercaseKey);
        while (pos != string::npos) {
            score++;
            pos = lowercaseQuestion.find(lowercaseKey, pos + 1);
        }
        if (score > bestMatchScore) {
            bestMatch = key;
            bestMatchScore = score;
        }
    }

    
    string response;
    if (!bestMatch.empty()) {
        response = responses[bestMatch];
        if (response.find("{min_days}") != string::npos) {
            // Replace placeholders with actual values
            response.replace(response.find("{min_days}"), 9, "3"); // Placeholder for minimum delivery days
            response.replace(response.find("{max_days}"), 9, "7"); // Placeholder for maximum delivery days
        }
        if (bestMatch == "order status") {
            string orderNumber;
            cout << "Myntra Rep: Please enter your order number: ";
            cin >> orderNumber;
            response += "\n I cannot access specific order details yet, but your order number is " + orderNumber + ". For detailed order information, please visit your Myntra account. Would you like help with anything else?";
        }
    } else {
        response = "I apologize, I couldn't quite understand that. Can you rephrase or ask something different? Perhaps you're looking for information about our popular categories like electronics or clothing?";
    }
    return response;
}

int main() {
    cout << greet() << endl;

    while (true) {
        string userInput;
        cout << "Customer: ";
        getline(cin, userInput);
        if (toLowercase(userInput) == "bye") {
            cout << "Myntra Rep: Thank you for contacting Myntra! Have a great day." << endl;
            break;
        }
        cout << "Myntra Rep: " << answer(userInput) << endl;
    }

    return 0;
}
