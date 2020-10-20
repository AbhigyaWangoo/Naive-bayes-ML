//
// Created by Abhigya Wangoo on 10/13/20.
//

#ifndef NAIVE_BAYES_IMAGE_MODEL_H
#define NAIVE_BAYES_IMAGE_MODEL_H

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

namespace naivebayes {
    /**
     * Trained model for specific Image
     */
    class ImageModel {
    public:
        /**
         * Overloaded functionality to output image model to file
         * 
         * @param ofs specifies file to output to 
         * @param image_model specifies the ImageModel to output
         * @return stream of output data
         */
        friend std::ofstream &operator<<(std::ofstream &ofs, ImageModel &image_model);

        /**
         * Finds class_probabilities_
         *
         * @return class_probabilities_
         */
        const std::map<char, double> &get_class_probabilities() const;

        /**
         * Finds pixel_probabilities_
         *
         * @return pixel_probabilities_
         */
        const std::multimap<char, double> &get_pixel_probabilities() const;
        
        /**
         * Constructs ImageModel with the class and pixel probabilities
         * 
         * @param class_probabilities to initialize with 
         * @param pixel_probabilities to initialize with
         */
        ImageModel(std::map<char, double> &class_probabilities, std::multimap<char, double> &pixel_probabilities);

        /**
         * Empty ImageModel constructor
         */
        ImageModel();
        
    private:
        std::map<char, double> class_probabilities_;
        std::multimap<char, double> pixel_probabilities_;
    };

}
#endif //NAIVE_BAYES_IMAGE_MODEL_H
