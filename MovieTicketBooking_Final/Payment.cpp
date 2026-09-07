// Abstraction: Payment defines the payment contract.
class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() {}
};
