<?php

namespace App\Filament\Resources;

use App\Filament\Resources\AccidentResource\Pages;
use App\Filament\Resources\AccidentResource\RelationManagers;
use Domain\Accidents\Models\Accident;
use Filament\Forms;
use Filament\Pages\Actions\Action;
use Filament\Resources\Form;
use Filament\Resources\Resource;
use Filament\Resources\Table;
use Filament\Tables;
use Illuminate\Database\Eloquent\Builder;
use Illuminate\Database\Eloquent\SoftDeletingScope;
use Illuminate\Support\Carbon;
use MatanYadaev\EloquentSpatial\Objects\Point;
use SebastiaanKloos\FilamentCodeEditor\Components\CodeEditor;

class AccidentResource extends Resource
{
    protected static ?string $model = Accident::class;

    protected static ?string $navigationIcon = 'heroicon-o-collection';

    public static function form(Form $form): Form
    {
        return $form
            ->schema([
                Forms\Components\TextInput::make('location')
                    ->autofocus()
                    ->required(),
                Forms\Components\DateTimePicker::make('date')
                    ->required()
                    ->default(now()),
                Forms\Components\Textarea::make('description')
                    ->required()
                    ->placeholder('e.g. A car crashed into a tree.')
                    ->columnSpanFull(),
                Forms\Components\TextInput::make('casualties')
                    ->required(),
                Forms\Components\TextInput::make('liability'),
                Forms\Components\Repeater::make('speed_samples')
                    ->schema([
                        Forms\Components\TextInput::make('speed')
                            ->required(),
                    ])
                    ->defaultItems(5)
                    ->collapsed(),
                Forms\Components\Repeater::make('rainfall_samples')
                    ->schema([
                        Forms\Components\TextInput::make('rainfall')
                            ->required(),
                    ])
                    ->defaultItems(5)
                    ->collapsed(),
            ]);
    }

    public static function table(Table $table): Table
    {
        return $table
            ->columns([
                Tables\Columns\TextColumn::make('location')
                    ->searchable()
                    ->sortable(),
                Tables\Columns\TextColumn::make('date')
                    ->searchable()
                    ->sortable()
                    ->dateTime('d/m/Y H:i'),
                Tables\Columns\TextColumn::make('description')
                    ->searchable()
                    ->sortable()
                    ->wrap(),
                Tables\Columns\TextColumn::make('casualties')
                    ->searchable()
                    ->sortable()
                    ->alignCenter(),
                Tables\Columns\TextColumn::make('liability')
                    ->searchable()
                    ->sortable()
                    ->placeholder('N/A'),
            ])
            ->filters([
                //
            ])
            ->actions([
//                Tables\Actions\EditAction::make(),
                Tables\Actions\Action::make('analyze')
                    ->label('Analyze')
                    ->icon('heroicon-o-chart-pie')
                    ->url(fn (Accident $record) => route('filament.resources.accidents.analyze', ['record' => $record->id])),
            ])
            ->bulkActions([
                Tables\Actions\DeleteBulkAction::make(),
            ]);
    }

    public static function getRelations(): array
    {
        return [
            //
        ];
    }

    public static function getPages(): array
    {
        return [
            'index' => Pages\ListAccidents::route('/'),
            'create' => Pages\CreateAccident::route('/create'),
            'edit' => Pages\EditAccident::route('/{record}/edit'),
            'analyze' => Pages\AccidentAnalysis::route('/{record}/analyze'),
        ];
    }
}
