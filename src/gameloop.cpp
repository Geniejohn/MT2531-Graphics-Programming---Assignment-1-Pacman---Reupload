		
        
        class GameLoop
{
    
    public:
        Gameloop()
        {

        }

        void run()
        {
            // Measure speed
            double currentTime = glfwGetTime();
            if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1sec ago
                                                    // printf and reset
                printf("%f ms/frame\n", 1000.0 / double(nbFrames));
                nbFrames = 0;
                lastTime += 1.0;
            }
        }

        ~Gameloop()
        {

        }
    
};
    

