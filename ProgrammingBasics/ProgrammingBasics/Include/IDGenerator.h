#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#define ID int

class IDGenerator
{
    public:
        static IDGenerator * getInstance(){
            if (_instance == nullptr )
                _instance  = new IDGenerator;
            return _instance;
        };

        ID generateID();
    private:
    IDGenerator();
    static IDGenerator *_instance;

    static ID _lastGiven;
};

#endif // IDGENERATOR_H
