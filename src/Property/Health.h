#ifndef HEALT_H
#define HEALT_H


class Health
{
    public:
        Health(){};

        void SetHealth(int health) { m_Health = health; }
        void DealDamage(int damage){ m_Health -= damage; }
        void RegenerateHealth (int health) { m_Health += health; }
        int GetHealth() { return m_Health; }

        virtual ~Health() {}

    private:
        int m_Health;
};

#endif // HEALT_H
