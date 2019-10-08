using System;


/*
    author      : Cathal McGivney
    date        : 16 / May / 2019
    description : Create objects of type Bike and EBike 
 */

namespace Question2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Question 2\n");

            // new Bike array of 4 elements
            Bike[] bikes = new Bike[4];


            Console.WriteLine("new Default Bike");
            // default Bike constructor
            bikes[0] = new Bike();
            bikes[0].Brand = "raleih";
            bikes[0].Price = 125.50;
            Console.WriteLine();

            Console.WriteLine("new Default EBike");
            // default EBike constructor
            EBike myEBike = new EBike();
            myEBike.Brand = "toyota";
            myEBike.Price = 700.50;
            myEBike.Power = 33;

            bikes[1] = myEBike;
            Console.WriteLine();

            Console.WriteLine("new Parametrised Bike");
            // parametrised Bike constructor
            bikes[2] = new Bike("brompton", 235.75);
            Console.WriteLine();

            Console.WriteLine("new Parametrised EBike");
            // parametrised EBike constructor
            bikes[3] = new EBike("rover", 800.50, 23);
            Console.WriteLine();

            Console.WriteLine("\n");

            // loop through array, calling toString method
            for (int i = 0; i < bikes.Length; i++)
            {
                Console.WriteLine(bikes[i].ToString());
            }
            Console.WriteLine("\n");
        }

    }


    class Bike
    {
        private string brand;
        private double price;
        private int frameNumber;

        private static int frameCounter = 1;

        // public int depositPerCent = 30;

        public string Brand { get => brand; set => brand = value; }
        public double Price { get => price; set => price = value; }
        public int FrameNumber { get => frameNumber;  }


        // default Bike constructor
        public Bike()
        {
            AssignFrameNumber();
            Console.WriteLine("default Bike constructor");
        }

        // parametrised Bike constructor
        public Bike(string argBrand, double argPrice)
        {
            Console.WriteLine("parametrised Bike constructor");
            AssignFrameNumber();
            Brand = argBrand;
            Price = argPrice;
        }

        private void AssignFrameNumber()
        {
            frameNumber = frameCounter;
            frameCounter++;
        }

        double CalcDeposit()
        {
            int depositPerCent = 30;
            return Price * depositPerCent * 0.01;
        }

        public override string ToString()
        {
            return String.Format("Brand: {0,-16}FrameNo: {1,-16}Price: {2,-16:0.00}Deposit: {3,-16:0.00}", Brand, FrameNumber, Price, CalcDeposit());
        }
    }

    class EBike : Bike
    {
        private int power;
        public int Power { get => power; set => power = value; }

        // default EBike constructor
        public EBike()
        {
            Console.WriteLine("default EBike constructor");
        }

        // parametrised EBike constructor
        public EBike(string argBrand, double argPrice, int argPower) : base( argBrand, argPrice )
        {
            Console.WriteLine("parametrised EBike constructor");
            Power = argPower;
        }

        double CalcDeposit()
        {
            int depositPerCent = 10;
            return Price * depositPerCent * 0.01;
        }

        public override string ToString()
        {
            return String.Format("Brand: {0,-16}FrameNo: {1,-16}Price: {2,-16:0.00}Deposit: {3,-16:0.00}Power: {4,-16}", Brand,FrameNumber, Price, CalcDeposit(), Power);
        }
    }
}
