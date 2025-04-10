#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <ctime>

int table_width = 105;
std::string get_current_date_time(){
    std::string date_time;
    time_t current_time;
    time(&current_time);
    date_time = ctime(&current_time);
    return date_time;
}
class Item{
private:
    std::string product_name;
    double unit_price;
    int quantity;
    double gross_price;
    double discount;
    double net_price;
    float discount_rate;
public:
    Item(std::string product_name, double unit_price, int quantity, float discount_rate = 0.10){
        this->product_name = product_name;
        this->unit_price = unit_price;
        this->quantity = quantity;
        this->gross_price = unit_price * quantity;
        this->discount_rate = discount_rate;
        this->discount = gross_price * this->discount_rate;
        this->net_price = this->gross_price - this->discount;
    }
    std::string getProductName(){
        return this->product_name;
    }

    int getQuantity(){
        return this->quantity;
    }

    double getUnitPrice(){
        return this->unit_price;
    }

    double getGrossPrice(){
        return this->gross_price;
    }

    double getDiscount(){
        return this->discount;
    }

    double getNetPrice(){
        return this->net_price;
    }

    double getDiscountRate(){
        return this->discount_rate;
    }

};
std::vector<std::string> split_string(std::string str, char delimeter){
    std::vector<std::string> string_parts;
    std::stringstream ss(str);
    std::string temp;
    while(getline(ss, temp, delimeter)){
        string_parts.push_back(temp);
    }

    return string_parts;
}

void write_table_header(std::ostream& output_stream){
    output_stream << std::string(table_width, '-') << '\n';
    output_stream << std::fixed << std::setprecision(2)<< '\n';
    output_stream << std::left << std::setw(15) << "Product" << std::right << std::setw(15)
            << "Unit Price" << std::setw(14) << "Quantity" << std::setw(15) << "Gross Total" << std::setw(20)
             << "Discount Rate(%)" << std::setw(15) <<  "Discount" << std::setw(11) << "Net Total" << '\n';
    output_stream << std::string(table_width, '-') << '\n';
}
void write_item_to_table(Item item, std::ostream& output_stream){
    output_stream << std::left << std::setw(15) << item.getProductName() << std::right << std::setw(15)
            << item.getUnitPrice() << std::setw(14) << item.getQuantity() << std::setw(15) << item.getGrossPrice() << std::setw(19)
             << (item.getDiscountRate() * 100) << std::setw(16) <<item.getDiscount() 
            << std::setw(10) << item.getNetPrice() << '\n';
}
void end_table(std::ostream& output_stream){
    output_stream << std::string(table_width, '-') << '\n';
}
void manual_entry_mode(std::ostream& output_file_stream){
    std::vector<Item> items;
    int number_of_products;
    std::cout << "How many products do you want to enter: ";
    std::cin >> number_of_products;

    for(int i = 0; i < number_of_products; i++){
        std::string product_name;
        double unit_price;
        int quantity;
        double discount_rate;
        char choice;
        std::cout << "Product number: " << i+1 << '\n';
        std::cout << "Enter the product name: ";
        std::cin >> product_name;
        std::cout << "Enter the unit price: ";
        std::cin >> unit_price;
        std::cout << "Enter the quantity: ";
        std::cin >> quantity;
        std::cout << "Do you wish to specify a discout rate? (if no discout rate is specified a default of 10% will be applied)\n"<<
         "Enter custom discount rate [y/n]: ";
        std::cin >>choice;
        if(choice == 'Y' || choice == 'y'){
            std::cout << "Enter the desired discount rate (between 0-100%): ";
            std::cin >> discount_rate;
            discount_rate = discount_rate/100;
            Item item(product_name, unit_price, quantity, discount_rate);
            items.push_back(item);
        }
        else{
            Item item(product_name, unit_price, quantity);
            items.push_back(item);
        }
        
    }
    double sum = 0;
    int size_of_item_collection = items.size();
    if(size_of_item_collection > 0){
        write_table_header(std::cout);
        write_table_header(output_file_stream);
        for(int i = 0; i < size_of_item_collection; i++){
            write_item_to_table(items[i], std::cout);
            write_item_to_table(items[i], output_file_stream);
            sum += items[i].getNetPrice();
        }
        end_table(std::cout);
        end_table(output_file_stream);
        output_file_stream << "Total: " << sum << '\n';
        std::cout << "Total: " << sum << '\n';
    }
    else{
        std::cout << "No Items were entered\n";
    }
}
void load_from_file(std::ostream& output_file_stream){
    std::string product_name;
    double unit_price;
    int quantity;
    double discount_rate;

    double sum;
    std::ifstream input("stock.txt");
    if(input.good()){
        std::string line;
        getline(input, line); //skipping the first line since its the heading
        write_table_header(std::cout);
        write_table_header(output_file_stream);
        while(getline(input, line)){
            std::vector<std::string> part_parameters = split_string(line, ' ');
            product_name = part_parameters[0];
            unit_price = std::atof(part_parameters[1].c_str());
            quantity = std::atof(part_parameters[2].c_str());

            Item item(product_name, unit_price, quantity);
            sum += item.getNetPrice();
            write_item_to_table(item, std::cout);
            write_item_to_table(item, output_file_stream);
        }
        input.close();
        end_table(std::cout);
        end_table(output_file_stream);
        std::cout << "Total: " << sum << '\n';
        output_file_stream << "Total: " << sum << '\n';
    }else{
        std::cout << "Error, file couldn't be opened successfully. probably because it doesn't exist";
    }

}
int main(){
    std::string zhong =     "⣿⣿⣿⣿⣿⣿⡿⠛⠋⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠛⠿⣿⣿⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⡿⠋⠁⠄⠄⢠⣴⣶⣿⣿⣶⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠿⣿⣿⣿⣿\n"
                            "⣿⣿⡟⠁⠄⠄⠄⠄⣿⣿⣿⣿⣿⣿⣇⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢹⣿⣿⣿\n"
                            "⣿⣿⣧⠄⠄⠄⠄⢰⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣸⣿⣿⣿\n"
                            "⣿⣿⣿⣧⡀⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⣷⣆⠄⠄⠄⠄⠄⠄⠄⠄⣰⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⡿⣦⣀⣾⣿⣟⣉⠉⠙⢛⡏⠁⠄⠄⠄⠄⠄⠄⠄⠄⠚⢿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣯⣗⣻⣿⣯⣥⣦⠄⣀⣾⡇⠄⠄⠂⠄⠄⠄⠄⠄⠄⠄⣼⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠂⠄⠄⠄⠄⠄⠄⠄⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⣻⠋⠄⠄⠄⠄⠄⠄⠄⢀⠄⣸⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡁⡀⠄⠄⠄⠄⠄⠄⢸⣾⣿⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣥⣾⣷⠶⠆⠄⠄⠄⢀⠄⠄⠄⠸⣿⣿⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⣿⢿⣿⣿⣿⣿⣿⣶⣄⡀⠄⠄⠄⠄⠄⢀⠄⠸⣿⣿⣿⣿⣿⣿\n"
                            "⣿⣿⣿⣿⣿⣿⠟⠚⣿⣿⡻⠿⠿⠛⠙⠁⠄⠄⠄⠄⠠⠂⠄⠄⠘⠿⣿⣿⣿⣿\n"
                            "⠿⠛⠉⠁⠁⠄⠄⠄⣻⣿⣿⣧⣠⣀⠄⠄⠄⠄⡀⠂⠄⠄⠄⠄⠄⠄⠈⠉⠿⢿\n"
                            "⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⠿⣿⡿⠃⢀⡠⠄⠃⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄\n";
   // std::cout << zhong << '\n';
   //can't print out zhong because cmd doesnt support the ascii chars used. if youre on linux just uncomment the 2 print zhong lines and youre golden
    
    int choice = 0;
    
    while(choice != 3){
        std::string current_date_time = get_current_date_time();
        std::cout << current_date_time << '\n';
        std::cout << "How do you wish to enter the items:\n1. Manually\n2. Load from file\n3. Quit Application\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::string option;
        //output filename is receipt_dayname_monthname_day_hh_mm_ss_yyyy
        std::vector<std::string> date_part_components = split_string(current_date_time, ' ');
        std::vector<std::string> time_components = split_string(date_part_components[3], ':');
        std::string output_file_name = "Receipts\\receipt_" + date_part_components[0] + '_' + date_part_components[1] + '_'+ date_part_components[2] + '_'+ time_components[0] + '_' + time_components[1] + '_' + time_components[2]  + '_' + split_string(date_part_components[4], '\n')[0] + ".txt";
        std::cout << output_file_name <<'\n';
        std::ofstream output_file_stream(output_file_name);
        output_file_stream << current_date_time << '\n';
        switch (choice)
        {
        case 1:
            manual_entry_mode(output_file_stream);
            output_file_stream.close();
            std::cout << "Are you done viewing the data [y]yes [n] no (Application will exit this view anyway no matter what you choose): ";
            std::cin >> option;
            break;
        case 2:
            load_from_file(output_file_stream);
            output_file_stream.close();
            std::cout << "Are you done viewing the data [y]yes [n] no (Application will exit this view anyway no matter what you choose): ";
            std::cin >> option;
            break;
        case 3:
            return 0;
            break;
        default:
            std::cout << "Invalid option Entered";
            break;
        }
    
    output_file_stream.close();
    system("cls");    
   // std::cout << zhong << '\n';
    
    }
   
    return 0;
}