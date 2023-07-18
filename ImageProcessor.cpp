#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cmath>



using namespace std;
bool Saved = false;

#define MaxRows 500
#define MaxCols 500

struct grayImage {

    grayImage() {
        /*
        The constructor function that is used to initialize the structure variables
        */
        Rows = Cols = 0;
        loaded = false;
        for (int r = 0; r < MaxRows; r++)
            for (int c = 0; c < MaxCols; c++)
                Image[r][c] = 0;
    }


    int setPixel(unsigned short value, int r, int c)
    {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        Image[r][c] = value;
        return value;
    }

    int getPixel(int r, int c)
    {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        return Image[r][c];
    }

    int setRows(int rows)
    {
        if (rows < 1 || rows > MaxRows)
            return -1;
        Rows = rows;
        return Rows;
    }

    int getRows()
    {
        return Rows;
    }

    int setCols(int cols)
    {
        if (cols < 1 || cols > MaxCols)
            return -1;
        Cols = cols;
        return Cols;
    }

    int getCols()
    {
        return Cols;
    }

    int Save(string File_Name)
    {
        /*
            This function will create an ASCII pgm file
            and store the contents of the the image in it
            Function must
                return 0 if successful
                1 if File_Name is not correct {it must end as .pgm}
                2 if unable to create a file

        */


         ofstream OUT(File_Name.c_str());

         if (File_Name.substr(File_Name.find_last_of(".") + 1) == "pgm")
         {
             loaded = true;
         }
         else
         {
             cout << "Error while saving ! .\nUnable to Save file (.pgm extension is missing) !\n\n";
             return 1;
         }


         if (loaded == true)
         {


            OUT << "P2" << endl;
            OUT << "# created by CodeXOwls" << endl;
            OUT << Cols << " " << Rows << endl;
            OUT << Maximum << endl;



            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    OUT << Image[i][j] << " ";

                }
                OUT << endl;

            }
            return 0;

            OUT.close();
         }
        else
        {
             cout << "Image not loaded ! \n\n";
             return 2;
        }


    }

    int load(string File_Name)
    {
        /*
            This function will read contents of an ASCII pgm file
            and store these contents in the variable and arry
            declared in this struct

                return 0 if successful
                1 if File_Name is not correct {it must end as .pgm}
                2 if unable to open the file for reading
        */

        string s;
        ifstream IN(File_Name.c_str());

        getline(IN, s);
        getline(IN, s);

        IN >> Cols >> Rows >> Maximum;

        int C, R;

        if (File_Name.substr(File_Name.find_last_of(".") + 1) == "pgm")
        {
            loaded = true;
        }
        else
        {
            cout << "Check Image(s) extension \n\n";
            return 1;
        }


        if (IN.is_open())
        {


            for (int i = 0; i < Rows; i++)
            {
                for (int j = 0; j < Cols; j++)
                {
                    IN >> Image[i][j];
                }
            }

            C = setCols(Cols);
            if (C == -1)
            {
                cout << "Error: Check Cols \n\n" << endl;
                return 2;

            }
            R = setRows(Rows);
            if (R == -1)
            {
                cout << "Error: Check Rows \n\n" << endl;
                return 2;
            }
            loaded = true;


        }
        else
        {
            cout << "Cannot load image(s) \n\n ";
            return 2;
        }


        IN.close();



        return 0;

    }
    void combineSideBySide(grayImage& Two, string FileName, unsigned short fillValue = 0) {

        int N = MaxCols - Cols;

        int C, colfrom;
        if (N > Two.Cols)
        {
            C = Cols + Two.Cols;
        }
        else
        {
            C = Cols + N;
        }

        int R;


        if (Rows > Two.Rows)
        {
            R = Rows;
        }
        else
        {
            R = Two.Rows;
        }

        int coltill, rowfrom;


        if (Rows < Two.Rows)
        {
            rowfrom = Rows;
            colfrom = 0;
            coltill = Cols;
        }
        else
        {
            rowfrom = Two.Rows;
            colfrom = Cols;
            coltill = C;

        }


        for (int i = 0; i < Two.Rows; i++)
        {
            for (int j = 0; j < N; j++)
            {

                Image[i][j + Cols] = Two.Image[i][j];



            }
        }



        for (int i = rowfrom; i < R; i++)
        {
            for (int j = colfrom; j < coltill; j++)
            {
                Image[i][j] = { fillValue };

            }
        }



        Rows = R;
        Cols = C;
        if (R > MaxRows || C > MaxCols)
        {
            cout << " Error while saving ! .\n.While combining exceeded 500 by 500 space ";
            return;
        }

        Save(FileName);





    }


    void combineTopToBottom(grayImage& Two, string FileName, unsigned short fillValue = 0) {
        /*
        This function must combine two images placing the first image on top and the second images
        on bottom.
        You must remember that the two images might not be equal in size and in such a case the
        the smaller image must be left-aligned with the larger image filling any extra columns
        with the gray color specified by the fillValue argument
        */
        int N = MaxRows - Rows;

        int R, colfrom;
        if (N > Two.Rows)
        {
            R = Rows + Two.Rows;
        }
        else
        {
            R = Rows + N;
        }

        int C;
        int coltill, rowfrom, rowtill;

        if (Cols > Two.Cols)
        {
            C = Cols;
            rowfrom = Rows;
            coltill = C;
            colfrom = Two.Cols;
        }
        else
        {
            C = Two.Cols;
            coltill = C;
            colfrom = Cols;
            rowfrom = 0;
        }



        if (Rows < Two.Rows)
        {

            rowtill = Rows;

        }
        else
        {
            rowtill = R;

        }

        if (R > MaxRows || C > MaxCols)
        {
            cout << " Error while saving ! .\n.While combining exceeded 500 by 500 space ";
            return;
        }


        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < C; j++)
            {

                Image[i + Rows][j] = Two.Image[i][j];



            }
        }



        for (int i = rowfrom; i < rowtill; i++)
        {
            for (int j = colfrom; j < coltill; j++)
            {
                Image[i][j] = { fillValue };

            }
        }


        Rows = R;
        Cols = C;
        Save(FileName);


    }

    void FadeIn(grayImage& second, int seconds, string BaseFileName, int frameRate = 30 ) {
        /*
        This function generate a sequence of seconds*frameRate images by taking average of corresponding pixel values
        Your first image must be the starting image and you must keep on creating new intermediate images by taking the
        average such that the second image gradually appears and first image fades away.

        Once again the two images might not be equal in size and in such a case the centers of the two images must be aligned.
        Here you can start by assuming that the two images have same size and relax the assumption later.
        */

        grayImage H;
        double StepSize = 1.0 / (frameRate * seconds);
        int Counter=0;

        int R,C,M;

        R = Rows;

        if (second.Rows > Rows)
        {
            R = second.Rows;
        }
        C = Cols;
        if (second.Cols > Cols)
        {
            C = second.Cols;
        }

        M = Maximum;
        if (second.Maximum > Maximum)
        {
            M = second.Maximum;
        }

        H.Rows = R;
        H.Cols = C;
        H.Maximum = M;


        for (double Alpha=1 ; Alpha >=0 ;Alpha-=StepSize)
        {
            for (int r = 0; r < R; r++)
            {
                for (int c = 0; c < C; c++)
                {
                    H.Image[r][c] = Image[r][c] * Alpha + (1 - Alpha) * second.Image[r][c];
                }
            }

            char N[10];

            itoa(Counter, N, 10);
            H.Save(BaseFileName + N + ".pgm");
            Counter++;
           /* if (Alpha - StepSize<0 && Alpha - StepSize>-StepSize)
            {
                Alpha = 0;
            }*/
        }

    }

    void Rotate(grayImage& RotatedImage, double angle = 90, int aboutx = 0, int abouty = 0)
    {
        /* This Function Has four explicit parameters
          angle : for counter clockwise direction the angle will be positive and negative for the clockwise direction
          aboutx and abouty: are the two points specifying the center of rotation
          RotatedImage: is a reference of a grayImage variable/structure. The rotated image will be placed in it
        */
        int  in, jn;
        angle = (angle * 3.1415192) / 180;

        RotatedImage.Rows = Rows;
        RotatedImage.Cols = Cols;
        RotatedImage.Maximum = Maximum;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {

                if (aboutx == 0 && abouty == 0)
                {
                    if (Rows % 2 == 0)
                    {
                        aboutx = Rows / 2;
                    }
                    else
                    {
                        aboutx = (Rows / 2) + 1;
                    }
                    if (Cols % 2 == 0)
                    {
                        abouty = Cols / 2;
                    }
                    else
                    {
                        abouty = (Cols / 2) + 1;
                    }
                }
                in = ((i - aboutx) * cos(angle) - (j - abouty) * sin(angle)) + aboutx;
                jn = ((j - abouty) * cos(angle) +  (i - aboutx) * sin(angle) + abouty);

                if (in > 0 && in < MaxRows && jn>0 && jn < MaxCols)
                {
                    RotatedImage.Image[in][jn] = Image[i][j];
                }

            }

        }

    }

    void Flip(int HorizontalOrVertical) {
        /*
         Parameter HorizontalOrVertical will be used to specify if the flip will be a horizontal flip or a vertical flip;
         The function will use one of the two private flip functions to do the task;
        */
        if (HorizontalOrVertical == 0)
        {
            FilpHorizontal();
        }
        else if (HorizontalOrVertical == 1)
        {
            FlipVerttical();
        }
    }

    void Negative() {
        /*
        Compute Negative image of an Image
        */


        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                Image[i][j] = Maximum - (Image[i][j]);
            }
        }

    }

    void changeBrightness(int amount) {
        /*
            Change the brightness level of an image by the amount specified by
            the amount parameter
        */
        int Check;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                Check = Image[i][j];
                if (amount > 0)
                {
                    if ((Check + amount) <= 255)
                    {
                        Image[i][j] = Image[i][j] + amount;

                    }
                    else
                    {
                        Image[i][j] = 255;

                    }
                }
                else if (amount < 0)
                {
                    if ((Check + (amount)) > 0)
                    {

                        Image[i][j] = Image[i][j] + amount;
                    }
                    else
                    {

                        Image[i][j] = 0;
                    }

                }

            }
        }

    }

    void Quantize(int Levels) {
        /*
        Apply the quantization
        */
        int l;
        l = 256 / Levels;

        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols; j++)
            {

                Image[i][j] = (Image[i][j] / l) * l;
            }
        }


    }
    void sortArray(int arrA[], int n)
    {
        int temp;

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (arrA[i] > arrA[j])
                {
                    temp = arrA[i];
                    arrA[i] = arrA[j];
                    arrA[j] = temp;
                }
            }
        }
    }

    void medianFilter(grayImage& Result, int filterSize = 3) {
        /*
            Apply median Filtering
        */
        int A[9];
        for (int i = 1; i <= Rows; i++)
        {
            for (int j = 1; j <= Cols; j++)
            {


                if (Image[i][j] == 0 || Image[i][j] == 255)
                {
                    A[0] = Image[i - 1][j];
                    A[1] = Image[i - 1][j - 1];
                    A[2] = Image[i - 1][j + 1];
                    A[3] = Image[i][j - 1];
                    A[4] = Image[i][j + 1];
                    A[5] = Image[i][j];
                    A[6] = Image[i + 1][j + 1];
                    A[7] = Image[i + 1][j];
                    A[8] = Image[i + 1][j - 1];
                    sortArray(A, 9);
                    Result.Image[i][j] = A[4];


                }
                else {

                    Result.Image[i][j] = Image[i][j];
                }
            }
        }

        Result.Cols = Cols;
        Result.Rows = Rows;
        Result.Maximum = Maximum;


    }

    void meanFilter(grayImage& Result, int filterSize = 3) {
        /*
            Apply mean Filtering
        */
        int A[9];
        int mean = 0;
        for (int i = 1; i <= Rows; i++)
        {
            for (int j = 1; j <= Cols; j++)
            {

                if (Image[i][j] < 200)
                {

                    A[0] = Image[i - 1][j];
                    A[1] = Image[i - 1][j - 1];
                    A[2] = Image[i - 1][j + 1];
                    A[3] = Image[i][j - 1];
                    A[4] = Image[i][j + 1];
                    A[5] = Image[i][j];
                    A[6] = Image[i + 1][j + 1];
                    A[7] = Image[i + 1][j];
                    A[8] = Image[i + 1][j - 1];


                    for (int k = 0; k < 9; k++)
                    {
                        mean += A[k];
                    }
                    mean = mean / 9;


                    Result.Image[i][j] = mean;
                }


            }
        }
        Result.Cols = Cols;
        Result.Rows = Rows;
        Result.Maximum = Maximum;

    }
    void Resize(grayImage& Result, int NR, int NC) {
        /*
            Change the number of rows to NewRows and Columns to New Columns
        */

        double colR, rowR;
        colR = NC;
        colR = colR / Cols;

        rowR = NR;
        rowR = rowR / Rows;


        for (int i = 0; i < NR; i++)
        {
            for (int j = 0; j < NC; j++)
            {
                int I, J;
                I = i / rowR;
                J = j / colR;

                Result.Image[i][j] = Image[I][J];
            }
        }


        Result.Cols = NC;
        Result.Rows = NR;
        Result.Maximum = 255;



    }

    void Resize(grayImage& Result, double Ratio) {
        /*
            Change the rows and columns by the ratio
        */
        int NR = Rows * Ratio;
        int NC = Cols * Ratio;

        if (NR > MaxRows || NC > MaxCols)
        {
            cout << " Error while saving ! .\n Exceeded limit of 500 by 500 while resizing !";
            return;
        }
        if (NR == 0 || NC == 0)
        {
            return;
        }

        Resize(Result, NR, NC);

    }

    void Transform(grayImage& Result, double Matrix[3][3]) {
        /*
            Apply General transformation represented by the matrix
        */
        double I, J,Z;
        int  NI, NJ;
        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0 ; j < Cols; j++)
            {
                I = ((i * Matrix[0][0]) + (j * Matrix[0][1]) + (Matrix[0][2]));
                J = ((i * Matrix[1][0]) + (j * Matrix[1][1]) + (Matrix[1][2]));
                Z= ((i * Matrix[2][0]) + (j * Matrix[2][1]) + (Matrix[2][2]));

                NI = I / Z;
                NJ = J / Z;

                if (NI >= 0 && NJ >= 0 && NI < MaxRows && NJ < MaxCols)
                {
                    Result.Image[NI][NJ] = Image[i][j];
                }
            }
        }

        Result.Rows = MaxRows;
        Result.Cols = MaxCols;
        Result.Maximum = Maximum;
    }

    void Filter(double Mask[3][3]) {
        /*
            Apply The filter mask on the image
        */
        double A;
        for (int i = 1; i <= Rows-1; i++)
        {
            for (int j = 1; j <= Cols-1; j++)
            {
                A = Image[i - 1][j - 1] * Mask[0][0];
                A = A + (Image[i - 1][j] * Mask[0][1]);
                A = A + (Image[i - 1][j+1] * Mask[0][2]);
                A = A + (Image[i][j-1] * Mask[1][0]);
                A = A + (Image[i][j] * Mask[1][1]);
                A = A + (Image[i][j+1] * Mask[1][2]);
                A = A + (Image[i+1][j -1] * Mask[2][0]);
                A = A + (Image[i + 1][j] * Mask[2][1]);
                A = A + (Image[i + 1][j + 1] * Mask[2][2]);

                Image[i][j] = A;

            }
        }

    }

    void DerivativeImage(grayImage& Result) {
        double V1, V2,D;
        double H[3][3] = { {-1,-1,-1},{0,0,0},{1,1,1} };
        double V[3][3] = { {-1,0,1},{-1,0,1},{-1,0,1} };

        for (int i = 1; i <= Rows - 1; i++)
        {
            for (int j = 1; j <= Cols - 1; j++)
            {
                V1 = Image[i - 1][j - 1] * H[0][0];
                V1 = V1 + (Image[i - 1][j] * H[0][1]);
                V1 = V1 + (Image[i - 1][j + 1] * H[0][2]);
                V1 = V1 + (Image[i][j - 1] * H[1][0]);
                V1 = V1 + (Image[i][j] * H[1][1]);
                V1 = V1 + (Image[i][j + 1] * H[1][2]);
                V1 = V1 + (Image[i + 1][j - 1] * H[2][0]);
                V1 = V1 + (Image[i + 1][j] * H[2][1]);
                V1 = V1 + (Image[i + 1][j + 1] * H[2][2]);


                V2 = Image[i - 1][j - 1] * V[0][0];
                V2 = V2 + (Image[i - 1][j] * V[0][1]);
                V2 = V2 + (Image[i - 1][j + 1] * V[0][2]);
                V2 = V2 + (Image[i][j - 1] * V[1][0]);
                V2 = V2 + (Image[i][j] * V[1][1]);
                V2 = V2 + (Image[i][j + 1] * V[1][2]);
                V2 = V2 + (Image[i + 1][j - 1] * V[2][0]);
                V2 = V2 + (Image[i + 1][j] * V[2][1]);
                V2 = V2 + (Image[i + 1][j + 1] * V[2][2]);

                D = sqrt((V1 * V1) + (V2 * V2));

                Result.Image[i][j] = D;

            }
        }

        Result.Rows = Rows;
        Result.Cols = Cols;
        Result.Maximum = Maximum;


    }
    void Crop(grayImage& Result, int T, int L, int R, int B)
    {
        Result.Rows = B - T;
        Result.Cols = R - L;
        Result.Maximum = Maximum;

        for (int i = 0; i < Result.Rows; i++)
        {
            for (int j = 0; j < Result.Cols; j++)
            {
                Result.Image[i][j] = Image[i+T][j+L];

            }
        }

    }
private:

    void FilpHorizontal() {
        /*
        Function for performing horizontal flip;

        }*/
        int Temp;
        for (int i = 0; i < Rows; i++)
        {
            for (int j = 0; j < Cols / 2; j++)
            {
                Temp = Image[i][Cols - j];
                Image[i][Cols - j] = Image[i][j];
                Image[i][j] = Temp;
            }
        }
    }

    void FlipVerttical() {
        /*
        Function for performing Vertical flip;
        */
        int Temp;


        for (int i = 0; i < Rows / 2; i++)
        {
            for (int j = 0; j < Cols; j++)
            {
                Temp = Image[Rows - i][j];
                Image[Rows - i][j] = Image[i][j];
                Image[i][j] = Temp;
            }
        }
    }




    void Fill(int L, int T, int R, int B, int FillValue) {
        for (int i = T; i <= B; i++)
            for (int j = L; j <= R; j++)
                Image[i][j] = FillValue;
    }

    unsigned short Image[MaxRows][MaxCols];
    int Rows, Cols, Maximum;
    bool loaded;
};

int main()
   {







   int Choice,ChoiceLoad,ChoiceSave, CombineChoiceS, CombineChoiceT,fr,sec,ChoiceF;

   cout << "\t\t\t\tWelcome to CodeXOwls Photo Editor" << endl;
   cout << "\t\t\t\t\t\tMenu " << endl;
   cout << "\t\t\t\tPress 0 :    To load first Image                    " << endl;
   cout << "\t\t\t\tPress 1 :    To Save Image                          " << endl;
   cout << "\t\t\t\tPress 2 :    To combine Images Side by Side         " << endl;
   cout << "\t\t\t\tPress 3 :    To combine Images Top to Bottom        " << endl;
   cout << "\t\t\t\tPress 4 :    To Apply Fade In transition            " << endl;
   cout << "\t\t\t\tPress 5 :    To Rotate Image                        " << endl;
   cout << "\t\t\t\tPress 6 :    To Flip Image Horizontally             " << endl;
   cout << "\t\t\t\tPress 7 :    To Flip Image  Vertically              " << endl;
   cout << "\t\t\t\tPress 8 :    For Negative of Image                  " << endl;
   cout << "\t\t\t\tPress 9 :    To change Brightness of Image          " << endl;
   cout << "\t\t\t\tPress 10:    For Quantize Image                     " << endl;
   cout << "\t\t\t\tPress 11:    To Apply Median Filter to Image        " << endl;
   cout << "\t\t\t\tPress 12:    To Apply Mean Filter to Image          " << endl;
   cout << "\t\t\t\tPress 13:    To Resize Image By Rows And Columns    " << endl;
   cout << "\t\t\t\tPress 14:    To Resize Image by Ratio               " << endl;
   cout << "\t\t\t\tPress 15:    To Transform Image                     " << endl;
   cout << "\t\t\t\tPress 16:    To Apply Filter To Image               " << endl;
   cout << "\t\t\t\tPress 17:    For Derivative Image                   " << endl;
   cout << "\t\t\t\tPress 18:    To Crop Image                          " << endl;
    string filename;
    string savename,Combinename,Fade;
    bool S1=false, S2=false;



    grayImage Image1, Image2, Extra1, Extra2;
    cout << "Enter your Choice " << endl;
    cin >> Choice;
    cout << endl;

    while (Choice != -1)

    {

        if (Choice == 0)
        {

            cout << "  Press 1 : If this is your first image  ." << endl;
            cout << "  Press 2 : If this is your second image . " << endl;
            cin >> ChoiceLoad;

            cout << " Enter name for loading file" << endl;
            cin >> filename;
            if (ChoiceLoad == 1)
            {
                int R=0;
                R=Image1.load(filename);

                if (R == 0)
                {
                    S1 = true;
                    cout << "\n\n Successfully loaded Image 1" << endl;
                }
                else
                {
                    return R;
                }

            }
            else if (ChoiceLoad == 2)
            {
                int R=0;
                R=Image2.load(filename);

                if (R == 0)
                {
                    S2 = true;
                    cout << "\n\n Successfully loaded Image 2" << endl;
                }
                else
                {
                    return R;
                }
            }


        }

        if (Choice == 1)
        {
            cout << "  Press 1 : To save your first image. " << endl;
            cout << "  Press 2 : To save your second image. " << endl;
            cin >> ChoiceSave;
            cout << " Enter name for saving file" << endl;
            cin >> savename;
            if (ChoiceSave == 1 && S1==true)
            {
                int R;

                R= Image1.Save(savename);
                if (R == 0)
                {
                    cout << "\n\n Successfully saved Image 1!" << endl;
                }
                else
                {
                    return R;
                }

            }
            else if (ChoiceSave == 2 && S2 == true)
            {
                int R;
                R=Image2.Save(savename);
                if (R == 0)
                {
                    cout << "\n\n Successfully saved Image 2!" << endl;
                }
                else
                {
                    return R;
                }
            }
            else
            {
                cout << "\n Your image is not loaded!"<<endl;
            }
        }

        if (Choice == 2)
        {
            int Fill;

            if (S1 == true && S2 == true)
            {
                cout << " Combining Images Side by Side... " << endl;
                cout << "  Press 1 : To combine images 1st then 2nd . " << endl;
                cout << "  Press 2 : To combine images 2nd then 1st . " << endl;
                cin >> CombineChoiceS;
                cout << endl;
                cout << "Enter a fill colour (0-255)" << endl;
                cin >> Fill;
                cout << endl;
                cout << " Enter name for saving this file" << endl;
                cin >> Combinename;

                if (CombineChoiceS == 1)
                {
                    cout << "\n\n Successfully combine image 1 and image 2 side-by-side !\n\n";
                    Image1.combineSideBySide(Image2, Combinename,Fill);
                }
                else if (CombineChoiceS == 2)
                {
                    cout << "\n\n Successfully combine image 2 and image 1 side-by-side !\n\n";
                    Image2.combineSideBySide(Image1, Combinename,Fill);
                }


            }
            else
            {
                cout << " Enter atleast two loaded images (one or both are missing)" << endl;
            }

        }
        if (Choice == 3)
        {
            int Fill;
            if (S1== true && S2==true)
            {
                cout << "  Combining Images Top to Botttom... " << endl;


                cout << "  Press 1 : To combine images 1st then 2nd. " << endl;
                cout << "  Press 2 : To combine images 2nd then 1st. " << endl;
                cin >> CombineChoiceT;
                cout << endl;
                cout << "Enter a fill colour (0-255)" << endl;
                cin >> Fill;
                cout << endl;
                cout << " Enter name for saving this file" << endl;
                cin >> Combinename;
                cout << endl;

                if (CombineChoiceT == 1)
                {
                    cout << "\n\n Successfully combine image 1 and image 2 top-to-bottom !\n\n";
                    Image1.combineTopToBottom(Image2, Combinename,Fill);
                }
                else if (CombineChoiceT == 2)
                {
                    cout << "\n\n Successfully combine image 2 and image 1 top-to-bottom !\n\n";
                    Image2.combineTopToBottom(Image1, Combinename,Fill);
                }
            }
            else
            {
                cout << "\n\n Enter atleast two loaded images (one or both are missing)!" << endl;
            }

        }
        if (Choice == 4)
        {
            cout << "Fade in ...." << endl;
            if (S1 == true && S2 == true)
            {
                cout << "Enter rate of frames per second "<<endl;
                cin >> fr;
                cout << endl;

                cout << "Enter time in seconds  " << endl;
                cin >> sec;
                cout << endl;

                cout << "What is name of your folder ?" << endl;
                cin >> Fade;
                cout << endl;


                cout << "  Press 1 : If you want to fade 1st image to 2nd image . " << endl;
                cout << "  Press 2 : If you want to fade 2nd image to 1st image ." << endl;
                cin >> ChoiceF;

                if (ChoiceF == 1)
                {
                    Image1.FadeIn(Image2, sec, Fade, fr);
                    cout << "\n\n Successfully applied fade-in to image 1 !\n\n";
                }
                else if (ChoiceF == 2)
                {
                    Image2.FadeIn(Image1, sec, Fade, fr);
                    cout << "\n\n Successfully applied fade-in to image 2 !\n\n";
                }

            }
            else
            {
                cout << "\n\n Enter atleast two loaded images (one or both are missing)" << endl;
            }
        }
        if (Choice == 5)
        {
            if (S1 == true || S2 == true)
            {
                int R, angle;
                grayImage Empty1, Empty2, Empty3, Empty4;
                string RotateS;

                cout << "Angle you want to rotate it to ? (in degrees).\n -tive sign for clockwise & +tive for anti-clockwise " << endl;
                cin >> angle;
                cout << endl;
                cout << "Enter the file name you want to save rotated image to ?" << endl;
                cin >> RotateS;
                cout << " Press 1 : To rotate first image . " << endl;
                cout << " Press 2 : To rotate second image ." << endl;
                cin >> R;
                if (R == 1 && S1 == true)
                {
                    Image1.Rotate(Empty1, angle, 0, 0);
                    Empty1.medianFilter(Empty2, 3);
                    cout << "\n\n Successfully rotated image 1\n\n";
                    Empty2.Save(RotateS);
                }
                else if(R==2 && S2==true)
                {
                    Image2.Rotate(Empty3, angle, 0, 0);
                    Empty3.medianFilter(Empty4, 3);
                    cout << "\n\n Successfully rotated image 2\n\n";
                    Empty4.Save(RotateS);
                }
                else if (R == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 6)
        {
            if (S1 == true || S2 == true)
            {
                int H;
                string HorizontalS;

                cout << "  Press 1 : To flip horizontally. " << endl;
                cout << "  Press 2 : To flip horizontally. " << endl;
                cin >> H;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> HorizontalS;

                if (H == 1 && S1 == true)
                {
                    Image1.Flip(0);
                    cout << "\n\n Successfully flipped image 1 horizontally !\n\n";
                    Image1.Save(HorizontalS);
                }
                else if (H == 2 && S2 == true)
                {
                    Image2.Flip(0);
                    cout << "\n\n Successfully flipped image 2 horizontally !\n\n";
                    Image2.Save(HorizontalS);
                }
                else if (H == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load at least 1 Image !" << endl;
            }

        }
        if (Choice == 7)
        {
            if (S1 == true || S2 == true)
            {
                int V;
                string VerticalS;

                cout << "  Press 1 : To flip vertically ." << endl;
                cout << "  Press 2 : To flip vertically ." << endl;
                cin >> V;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> VerticalS;

                if (V == 1 && S1 == true)
                {
                    Image1.Flip(1);
                    cout << "\n\n Successfully flipped image 1 vertically !\n\n";
                    Image1.Save(VerticalS);
                }
                else if (V == 2 && S2 == true)
                {
                    Image2.Flip(1);
                    cout << "\n\n Successfully flipped image 2 vertically !\n\n";
                    Image2.Save(VerticalS);
                }
                else if (V == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 8)
        {
            if (S1 == true || S2 == true)
            {
                int N;
                string Negative;

                cout << "  Press 1 : To create negative image of 1st image . " << endl;
                cout << "  Press 2 : To create negative image of 2nd image . " << endl;
                cin >> N;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> Negative;

                if (N == 1 && S1 == true)
                {
                    Image1.Negative();
                    cout << "\n\n Successfully created negative of image 1 !\n\n";
                    Image1.Save(Negative);
                }
                else if (N == 2&& S2 == true)
                {
                    Image2.Negative();
                    cout << "\n\n Successfully created negative of image 2 !\n\n";
                    Image2.Save(Negative);
                }
                else if (N == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 9)
        {
            if (S1 == true || S2 == true)
            {
                int B, P;
                string Brightness;

                cout << "  Press 1 : To change brightness of 1st image ." << endl;
                cout << "  Press 2 : To change brightness of 2nd image ." << endl;
                cin >> P;
                cout << endl;
                cout << "By what factor ?(to increase enter +tive value & to dim -tive)" << endl;
                cin >> B;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> Brightness;

                if (P == 1&& S1 ==true)
                {
                    Image1.changeBrightness(B);
                    cout << "\n\n Successfully applied brightness on image 1 !\n\n";
                    Image1.Save(Brightness);
                }
                else if (P == 2 && S2 == true)
                {
                    Image2.changeBrightness(B);
                    cout << "\n\n Successfully applied brightness on image 2 !\n\n";
                    Image2.Save(Brightness);
                }
                else if (P == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }

        }
        if (Choice == 10)
        {
            if (S1 == true || S2 == true)
            {
                int Q, Level;
                string quantize;

                cout << "  Press 1 : To quantize 1st image ." << endl;
                cout << "  Press 2 : To quantize 2nd image  ." << endl;
                cin >> Q;
                cout << endl;
                cout << "Levels ? " << endl;
                cin >> Level;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> quantize;

                if (Q == 1 && S1== true)
                {
                    Image1.Quantize(Level);
                    cout << "\n\n Successfully applied quantization on image 1 !\n\n";
                    Image1.Save(quantize);
                }
                else if (Q == 2 && S2 == true)
                {
                    Image2.Quantize(Level);
                    cout << "\n\n Successfully applied quantization on image 2 !\n\n";
                    Image2.Save(quantize);
                }
                else if (Q == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }

        }
        if (Choice == 11)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int Med;
                string Median;

                cout << "  Press 1 : To apply median filter on 1st image ." << endl;
                cout << "  Press 2 : To apply median filter on 2nd image ." << endl;
                cin >> Med;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> Median;

                if (Med == 1 && S1 == true)
                {
                    Image1.medianFilter(Empty1);
                    cout << "\n\n Successfully applied median filter on image 1 !\n\n";
                    Empty1.Save(Median);
                }
                else if (Med == 2 && S2 == true)
                {
                    Image2.medianFilter(Empty2, 3);
                    cout << "\n\n Successfully applied median filter on image 2 !\n\n";
                    Empty2.Save(Median);
                }
                else if (Med == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 12)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int M;
                string Mean;

                cout << "  Press 1 : To apply mean filter on 1st image ." << endl;
                cout << "  Press 2 : To apply mean filter on 2nd image ." << endl;
                cin >> M;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> Mean;

                if (M == 1 && S1 == true)
                {
                    Image1.meanFilter(Empty1);
                    cout << "\n\n Successfully applied mean filter on image 1 !\n\n";
                    Empty1.Save(Mean);
                }
                else if (M == 2 && S2 == true)
                {
                    Image2.meanFilter(Empty2, 3);
                    cout << "\n\n Successfully applied mean filter on image 2 !\n\n";
                    Empty2.Save(Mean);
                }
                else if (M == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }

        }
        if (Choice == 13)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int R, nr, nc;
                string resized;

                cout << "Enter new rows " << endl;
                cin >> nr;
                cout << endl;
                cout << "Enter new columns " << endl;
                cin >> nc;
                cout << endl;

                cout << "  Press 1 : To resize 1st image. " << endl;
                cout << "  Press 2 : To resize 2nd image. " << endl;
                cin >> R;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> resized;

                if (R == 1 && S1 ==true)
                {
                    cout << "\n\n Successfully resized image 1 !\n\n";
                    Image1.Resize(Empty1, nr, nc);
                    Empty1.Save(resized);
                }
                else if (R == 2 && S2== true)
                {
                    cout << "\n\n Successfully resized image 2 !\n\n";
                    Image2.Resize(Empty2, nr, nc);
                    Empty2.Save(resized);
                }
                else if(R==1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 14)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int R, ratio;
                string resize;

                cout << "Enter new ratio " << endl;
                cin >> ratio;
                cout << endl;

                cout << "  Press 1 : To resize 1st image ." << endl;
                cout << "  Press 2 : To resize 2nd image ." << endl;
                cin >> R;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> resize;

                if (R == 1 && S1 == true)
                {
                    cout << "\n\n Successfully resized image 1 !\n\n";
                    Image1.Resize(Empty1, ratio);
                    Empty1.Save(resize);
                }
                else if (R == 2 && S2 == true)
                {
                    cout << "\n\n Successfully resized image 2 !\n\n";
                    Image2.Resize(Empty2, ratio);
                    Empty2.Save(resize);
                }
                else if (R == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 15)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int T;
                string transform;
                double Array[3][3];

                cout << "Enter a matrix of 3x3 " << endl;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        cin >> Array[i][j];
                    }
                }

                cout << endl;

                cout << "  Press 1 : To transform 1st image ." << endl;
                cout << "  Press 2 : To transform 2nd image  ." << endl;
                cin >> T;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> transform;

                if (T == 1 && S1 == true)
                {
                    Image1.Transform(Empty1, Array);
                    cout << "\n\n Successfully transformed image 1 !\n\n";
                    Empty1.Save(transform);
                }
                else if (T == 2 && S2 == true)
                {
                    Image2.Transform(Empty2, Array);
                    cout << "\n\n Successfully transformed image 2 !\n\n";
                    Empty2.Save(transform);
                }
                else if (T == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 16)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int Fi;
                string filters;
                double Array[3][3];

                cout << "Enter a matrix of 3x3 " << endl;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        cin >> Array[i][j];
                    }
                }

                cout << endl;

                cout << "  Press 1 : To apply filter on 1st image ." << endl;
                cout << "  Press 2 : To apply filter on 2nd image ." << endl;
                cin >> Fi;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> filters;

                if (Fi == 1 && S1 == true)
                {
                    Image1.Filter(Array);
                    cout << "\n\n Successfully applied filter of your matrix given on image 1 !\n\n";
                    Image1.Save(filters);
                }
                else if (Fi == 2 && S2 == true)
                {
                    Image2.Filter(Array);
                    cout << "\n\n Successfully applied filter of your matrix given on image 2 !\n\n";
                    Image2.Save(filters);
                }
                else if (Fi == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }
        }
        if (Choice == 17)
        {
            if (S1 == true || S2 == true)
            {
                grayImage Empty1, Empty2;
                int D;
                string derivate;
                cout << endl;

                cout << "  Press 1 : To derivate on 1st image." << endl;
                cout << "  Press 2 : To derivate on 2nd image ." << endl;
                cin >> D;
                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> derivate;

                if (D == 1 && S1 == true)
                {
                    Image1.DerivativeImage(Empty1);
                    cout << "\n\n Successfully applied derivative on image 1 !\n\n";
                    Empty1.Save(derivate);
                }
                else if (D == 2 && S2 == true)
                {
                    Image2.DerivativeImage(Empty2);
                    cout << "\n\n Successfully applied derivative on image 2 !\n\n";
                    Empty2.Save(derivate);
                }
                else if (D == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }

        }
        if (Choice == 18)
        {
            if (S1 == true || S2 == true)
            {
                int l, r, t, b, C;
                string crop;
                grayImage Empty1, Empty2;
                cout << "Enter Top " << endl;
                cin >> t;
                cout << endl;
                cout << "Enter Bottom " << endl;
                cin >> b;
                cout << endl;
                cout << "Enter Left " << endl;
                cin >> l;
                cout << endl;
                cout << "Enter Right " << endl;
                cin >> r;
                cout << endl;

                cout << "  Press 1 : To crop 1st image ." << endl;
                cout << "  Press 2 : To crop 2nd image ." << endl;
                cin >> C;

                cout << endl;
                cout << "Enter name of file you want it to be saved as ?" << endl;
                cin >> crop;

                if (C == 1 && S1 == true)
                {
                    Image1.Crop(Empty1, t, l, r, b);
                    cout << "\n\n Successfully cropped image 1 !\n\n";
                    Empty1.Save(crop);
                }
                else if (C == 2 && S2 == true)
                {
                    Image2.Crop(Empty2, t, l, r, b);
                    cout << "\n\n Successfully cropped image 2 !\n\n";
                    Empty2.Save(crop);
                }
                else if (C == 1)
                {
                    cout << "\n\n You have not loaded image 1 ! " << endl;
                }
                else
                {
                    cout << "\n\n You have not loaded image 2 ! " << endl;
                }
            }
            else
            {
                cout << "\n\n Load atleast 1 Image !" << endl;
            }


        }



        cout <<"\n Press again to perform another function on image :)  (press -1 to stop) "<< endl;
        cin >> Choice;
        cout << endl;



    }


    return 0;
}
