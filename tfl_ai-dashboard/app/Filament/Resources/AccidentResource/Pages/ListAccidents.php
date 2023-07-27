<?php

namespace App\Filament\Resources\AccidentResource\Pages;

use App\Filament\Resources\AccidentResource;
use Filament\Pages\Actions;
use Filament\Resources\Pages\ListRecords;

class ListAccidents extends ListRecords
{
    protected static string $resource = AccidentResource::class;

    protected function getActions(): array
    {
        return [
            Actions\CreateAction::make(),
        ];
    }
}
