#include <iostream>
#include <string>
#include <curl/curl.h> // Include the cURL library for handling API calls

// Function to send a request to the API
std::string send_request(const std::string& prompt) {
    CURL* curl; // Declare a pointer for cURL handle
    CURLcode res; // Variable to store the result of the cURL operation
    std::string response_data; // String to store the response from the API

    curl = curl_easy_init(); // Initialize cURL
    if(curl) { // Check if cURL initialization was successful
        struct curl_slist* headers = NULL; // Declare a pointer for HTTP headers
        // Append the Content-Type header and Authorization header with the provided API key
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer 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"); // Use the API key you provided

        // Prepare the data to be sent in the POST request, which includes the model, prompt, and max tokens
        std::string data = "{\"model\":\"text-davinci-003\",\"prompt\":\"" + prompt + "\",\"max_tokens\":100}";

        // Set the URL for the API endpoint
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/completions");
        // Set the HTTP headers
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        // Set the POST data (i.e., the JSON data we just created)
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        // Define the write function to handle the API's response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](void* contents, size_t size, size_t nmemb, std::string* s) {
            s->append((char*)contents, size * nmemb); // Append the response to the response_data string
            return size * nmemb; // Return the number of bytes processed
        });
        // Set the pointer for the write function to modify
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

        // Perform the cURL request
        res = curl_easy_perform(curl);
        // If the request fails, display an error message
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        // Clean up and release cURL resources after the request is completed
        curl_easy_cleanup(curl);
    }
    // Return the response data that was received from the API
    return response_data;
}

int main() {
    std::string user_input; // Variable to store user input
    std::cout << "Enter your question: "; // Prompt the user to enter a question
    getline(std::cin, user_input); // Read the user input

    std::cout << "Processing...\n"; // Inform the user that the request is being processed
    // Call the send_request function to get the AI response for the user's input
    std::string response = send_request(user_input);

    // Display the response from the AI
    std::cout << "AI Response: " << response << std::endl;

    return 0; // Exit the program
}
