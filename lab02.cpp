#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

class Time {
private:
    int seconds;

public:
    Time(int sec = 0) : seconds(sec) {}

    int to_seconds() const { return seconds; }

    Time operator+(const Time& other) const { return seconds + other.seconds; }
    Time operator-(const Time& other) const { return seconds - other.seconds; }
    Time operator*(int scalar) const { return seconds * scalar; }

    friend std::ostream& operator<<(std::ostream& os, const Time& t) {
        os << (t.seconds / 60) << "m" << (t.seconds % 60) << "s";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Time& t) {
        int m, s;
        is >> m >> s;
        t.seconds = m * 60 + s;
        return is;
    }
};

// Klasa Item
class Item {
private:
    std::string name;
    double unit_net_price;
    char vat_type;
    int quantity;

public:
    Item(const std::string& n, double price, char vat, int qty)
        : name(n), unit_net_price(price), vat_type(vat), quantity(qty) {}

    double get_net_total() const { return unit_net_price * quantity; }
    double get_vat_rate() const { return vat_type == 'A' ? 0.23 : vat_type == 'B' ? 0.08 : 0.0; }
    double get_total() const { return get_net_total() * (1 + get_vat_rate()); }

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << std::left << std::setw(15) << item.name << " | "
           << std::fixed << std::setprecision(2)
           << std::setw(5) << item.unit_net_price << " "
           << item.vat_type << " | "
           << std::setw(3) << item.quantity << " | "
           << std::setw(6) << item.get_net_total() << " | "
           << item.get_total();
        return os;
    }
};

class Invoice {
private:
    std::string seller_nip;
    std::string buyer_nip;
    std::vector<Item> items;

public:
    Invoice(const std::string& seller, const std::string& buyer)
        : seller_nip(seller), buyer_nip(buyer) {}

    void add_item(const Item& item) { items.push_back(item); }

    friend std::ostream& operator<<(std::ostream& os, const Invoice& inv) {
        os << "------------------VAT invoice------------------\n"
           << "===============================================\n"
           << "Seller: " << inv.seller_nip << "      Buyer: " << inv.buyer_nip << "\n\n"
           << "                  c.j. VAT   il.    net   total\n";

        double total_net = 0.0, total_gross = 0.0;
        for (size_t i = 0; i < inv.items.size(); ++i) {
            os << std::setw(2) << (i + 1) << ". " << inv.items[i] << "\n";
            total_net += inv.items[i].get_net_total();
            total_gross += inv.items[i].get_total();
        }
        os << "------------------------------------ TOTAL ----\n"
           << std::right << std::setw(38) << total_net << " | " << total_gross;
        return os;
    }
};

int main() {

    std::cout << "=== Time ===\n";
    Time t1(200);
    std::cout << "Time t1: " << t1 << "\n";

    Time t2;
    std::cout << "Enter time in minutes and seconds (e.g., 10 12): ";
    std::cin >> t2;
    std::cout << "Time t2: " << t2 << "\n";

    Time t3 = t2 - t1;
    std::cout << "Difference (t2 - t1): " << t3 << "\n";
    std::cout << "Difference in seconds: " << t3.to_seconds() << "\n";

    std::cout << "\n";

    std::cout << "=== Invoice ===\n";
    Invoice inv("7770003699", "0123456789");
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    std::cout << inv << "\n";

    return 0;
}
