#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <utility>

#include "../model/point.h"
#include "../model/link.h"
#include "../model/figure_details.h"
#include "../managers/draw/draw_manager.h"


class Figure : public Object {
    friend void DrawManager::execute();

public:
    Figure() : _figureDetails(new FigureDetails) {}
    Figure(const Figure &model);
    explicit Figure(const std::shared_ptr<FigureDetails> &figureDetails) : _figureDetails(figureDetails) {}
    ~Figure() override = default;

    virtual bool isVisible();

    void accept(Visitor *visitor) override;
    bool isComposite() override;

protected:
    std::shared_ptr<FigureDetails> _figureDetails;
};

#endif
