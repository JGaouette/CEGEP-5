class Client {
    static instance = 0;
    ID = 0;

    constructor() {
        this.ID = Client.instance++;
    }
}

