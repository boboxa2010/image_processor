add_executable(
        image_processor
        image_processor.cpp
        Image.cpp Image.h BMP.cpp BMP.h Filter.h BMP.cpp BMP.cpp BMP.h NegativeFilter.cpp NegativeFilter.h ChannelWiseFilter.cpp ChannelWiseFilter.h CompositeFilter.cpp CompositeFilter.h CropFilter.cpp CropFilter.h GrayscaleFilter.cpp GrayscaleFilter.h ConvFilter.cpp ConvFilter.h SharpeningFilter.h Threshold.cpp Threshold.h EdgeDetectionFilter.h EdgeDetectionFilter.cpp Parser.cpp Parser.h Crystallize.cpp Crystallize.h Blur.cpp Blur.h)

add_catch(test_crop BMP.cpp Image.cpp CropFilter.cpp test_crop.cpp ChannelWiseFilter.cpp)

add_catch(test_grayscale BMP.cpp Image.cpp GrayscaleFilter.cpp test_grayscale.cpp)

add_catch(test_reading_writing BMP.cpp Image.cpp test_reading_writing.cpp)

add_catch(test_parse Image.cpp Parser.cpp ChannelWiseFilter.cpp GrayscaleFilter.cpp CropFilter.cpp Crystallize.cpp ConvFilter.cpp NegativeFilter.cpp CompositeFilter.cpp EdgeDetectionFilter.cpp Threshold.cpp test_parse.cpp)

add_catch(test_negative BMP.cpp Image.cpp NegativeFilter.cpp test_negative.cpp ChannelWiseFilter.cpp)

add_catch(test_sharp BMP.cpp Image.cpp test_sharp.cpp ConvFilter.cpp ChannelWiseFilter.cpp)

add_catch(test_edge BMP.cpp Image.cpp ConvFilter.cpp ChannelWiseFilter.cpp CompositeFilter.cpp EdgeDetectionFilter.cpp Threshold.cpp test_edge.cpp)

add_catch(test_crystallize BMP.cpp Image.cpp Crystallize.cpp test_crystallize.cpp)

add_catch(test_blur BMP.cpp Image.cpp ChannelWiseFilter.cpp Blur.cpp BMP.cpp test_blur.cpp)